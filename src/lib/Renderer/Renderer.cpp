#include "../../lib/Renderer/Renderer.h"
#include <unordered_set>
#include <thread>

#include "Material.h"
#include "../Game/DateTime.h"
#include "../Window/Window.h"

/// Initializuje shadery i tekstury
Renderer::Renderer() {
    crosshair = new CrosshairMesh();
    glGenFramebuffers(1, &depthMapFBO);

    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    depthTestMaterial.shader->use();
    depthTestMaterial.shader->setInt("depthMap", 1);
}

/// Czyści ekran kolorem z DateTime::getSkyColor()
void Renderer::Clear() {
    glm::vec3 color = DateTime::getSkyColor();
    glClearColor(color.x, color.y, color.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(
    const Player &player,
    const std::unordered_map<std::pair<int, int>, Chunk, PairHash> &chunks
) {
    UpdateLighting();
    UpdateProjection(player);

    AddChunk();
    RemoveChunks();

    glBindTexture(GL_TEXTURE_2D, depthMap);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    Clear();

    float near_plane = 1.0f, far_plane = 1000.0f;
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    glm::mat4 lightView = glm::lookAt(DateTime::getSunPos() * 10.0f, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 lightSpaceMatrix = lightProjection * lightView;
    // render scene from light's point of view

    shadowMappingMaterial.shader->use();
    shadowMappingMaterial.shader->setMat4("lightSpaceMatrix", lightSpaceMatrix);

    worldMaterial.Use(0);
    DrawChunks();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 2. then render scene as normal with shadow mapping (using depth map)
    glViewport(0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
    Clear();
    sunAndMoon.Draw();

    worldMaterial.Use(0);
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    worldMaterial.shader->setMat4("lightSpaceMatrix", lightSpaceMatrix);
    DrawChunks();

    crosshairMaterial.Use(0);
    crosshair->draw();

    depthTestMaterial.Use(0);
    depthTestMaterial.shader->setMat4("lightSpaceMatrix", lightSpaceMatrix);
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, depthMap);

    mesh.draw();
}


void Renderer::AddChunk() {
    if (chunksToAdd.size() == 0) return;
    if (!isReadyToAdd) return;

    ChunkBuilder chunk = chunksToAdd[chunksToAdd.size() - 1];
    int x = chunk.chunk.x;
    int z = chunk.chunk.z;

    auto mesh = ChunkMesh(x, z);
    mesh.positions = chunk.positions;
    mesh.textures = chunk.textures;
    mesh.normals = chunk.normals;
    mesh.ambientOcclusions = chunk.ambientOcclusions;
    mesh.updateBuffers();
    chunkMeshes[{x, z}] = mesh;
    chunksToAdd.pop_back();
}

void Renderer::RemoveChunks() {
    if (chunksToRemove.size() == 0) return;
    auto p = chunksToRemove[chunksToRemove.size() - 1];
    chunkMeshes.erase(p);
    chunksToRemove.pop_back();
}

void Renderer::DrawChunks() {
    for (auto chunkMeshPair: chunkMeshes) {
        ChunkMesh chunkMesh = chunkMeshPair.second;
        chunkMesh.draw();
    }
}

void Renderer::UpdateProjection(const Player &player) const {
    const glm::mat4 projection = glm::perspective(45.0f, (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT, 0.1f, 1000.0f);
    const glm::mat4 view = player.camera.GetViewMatrix();

    sunAndMoon.material->shader->use();
    sunAndMoon.material->shader->setMat4("projection", projection);
    sunAndMoon.material->shader->setMat4("view", view);

    depthTestMaterial.shader->use();
    depthTestMaterial.shader->setMat4("projection", projection);
    depthTestMaterial.shader->setMat4("view", view);
    depthTestMaterial.shader->setInt("shadowMap", 1);
    glm::mat4 model = glm::mat4(1.0f);
    model = translate(model, glm::vec3(0.0, 5.0, 0.0));

    depthTestMaterial.shader->setMat4("model", model);


    worldMaterial.shader->use();
    worldMaterial.shader->setMat4("projection", projection);
    worldMaterial.shader->setMat4("view", view);
    worldMaterial.shader->setVec3("viewPos", player.camera.Position);

    const glm::mat4 orthoProjection = glm::ortho(0.0f, 1600.0f, 0.0f, 900.0f, -1.0f, 1.0f);
    crosshairMaterial.shader->use();
    crosshairMaterial.shader->setMat4("projection", orthoProjection);
}

void Renderer::UpdateLighting() const {
    worldMaterial.shader->use();
    worldMaterial.shader->setInt("material.diffuse",0);
    worldMaterial.shader->setInt("material.specular", 0);
    worldMaterial.shader->setFloat("material.shininess", 0.0f);

    const float ambient = 0.3;
    const auto lightPos = DateTime::getSunPos();

    worldMaterial.shader->setVec3("light.direction", -lightPos);
    worldMaterial.shader->setVec3("light.ambient", ambient, ambient, ambient);
    worldMaterial.shader->setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
    worldMaterial.shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

    glm::vec2 uvScale(1.0f / 8, 1.0f / 8);
    worldMaterial.shader->setVec2("uvScale", uvScale);
}
