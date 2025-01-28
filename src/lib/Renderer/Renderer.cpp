#include "../../lib/Renderer/Renderer.h"
#include <unordered_set>
#include <thread>

#include "Material.h"
#include "../Game/DateTime.h"
#include "../Window/Window.h"

/// Initializuje shadery i tekstury
Renderer::Renderer() {
    crosshair = new CrosshairMesh();
}

/// Czyści ekran kolorem z DateTime::getSkyColor()
void Renderer::Clear() {
    glm::vec3 color = DateTime::getSkyColor();
    glClearColor(color.x, color.y, color.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(
    const Player &player
) {
    UpdateProjection(player);

    AddChunk();
    RemoveChunks();

    Clear();
    sunAndMoon.Draw();

    worldMaterial.Use(0);
    DrawChunks();

    crosshairMaterial.Use(0);
    crosshair->draw();
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

    worldMaterial.shader->use();
    worldMaterial.shader->setMat4("projection", projection);
    worldMaterial.shader->setMat4("view", view);
    worldMaterial.shader->setVec3("viewPos", player.camera.Position);

    glm::vec2 uvScale(1.0f / 8, 1.0f / 8);
    worldMaterial.shader->setVec2("uvScale", uvScale);

    const glm::mat4 orthoProjection = glm::ortho(0.0f, 1600.0f, 0.0f, 900.0f, -1.0f, 1.0f);
    crosshairMaterial.shader->use();
    crosshairMaterial.shader->setMat4("projection", orthoProjection);
}
