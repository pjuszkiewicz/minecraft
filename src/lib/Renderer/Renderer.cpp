#include "../../lib/Renderer/Renderer.h"
#include <unordered_set>
#include <thread>

#include "../Game/DateTime.h"

/// Initializuje shadery i tekstury
Renderer::Renderer() {
    const std::string ASSETS_PATH = "/Users/piotr/Development/C++/minecraft/src/assets";
    // const std::string ASSETS_PATH = "/home/piotr/Development/C++/minecraft/src/assets";

    sunAndMoonShader = new Shader((ASSETS_PATH + "/shaders/example/vertex.vs").c_str(),
                           (ASSETS_PATH + "/shaders/example/fragment.fs").c_str());

    instancedShader = new Shader((ASSETS_PATH + "/shaders/example/instanced.vs").c_str(),
                                 (ASSETS_PATH + "/shaders/example/instanced.fs").c_str());

    uiShader = new Shader((ASSETS_PATH + "/shaders/example/ui_vertex.vs").c_str(),
                          (ASSETS_PATH + "/shaders/example/ui_fragment.fs").c_str());


    texturePack = new Texture((ASSETS_PATH + "/textures/texturepack.png").c_str(), GL_RGBA);
    crosshair = new Crosshair();

    // shadow test
    depthTestShader = new Shader((ASSETS_PATH + "/shaders/example/depthTest.vs").c_str(),
                            (ASSETS_PATH + "/shaders/example/depthTest.fs").c_str());
    depthTestShader->use();
    depthTestShader->setInt("depthMap", 0);
    depthShader = new Shader((ASSETS_PATH + "/shaders/example/depth.vs").c_str(),
                             (ASSETS_PATH + "/shaders/example/depth.fs").c_str());
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

    // 1. first render to depth map
    glm::vec3 sunPos = glm::vec3(10, 10, 10);
    auto lightView = glm::lookAt(sunPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 1000.0f);
    glm::mat4 lightSpaceMatrix = lightProjection * lightView;

    shadowMap.use(0);
    depthShader->use();
    depthShader->setInt("shadowMap", 0);
    depthShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowMap.depthMapFBO);
    Clear();
    depthShader->use();
    depthShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);
    DrawChunks();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    glViewport(0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
    Clear();
    DrawMoon(player);
    DrawSun(player);

    texturePack->use(0);
    instancedShader->use();
    DrawChunks();

    uiShader->use();
    crosshair->draw();

    DrawTestMesh();
}

void Renderer::DrawTestMesh() const {
    auto model = glm::mat4(1.0f);
    auto pos = glm::vec3(0, 10, 0);
    model = translate(model, pos);

    shadowMap.use(0);
    depthTestShader->use();
    depthTestShader->setMat4("model", model);
    depthTestShader->setInt("depthMap", 0);
    depthTestShader->setFloat("near_plane", 0.1f);
    depthTestShader->setFloat("far_plane", 1000.0f);;
    mesh.draw();
}

void Renderer::DrawSun(const Player &player) {
    auto model = glm::mat4(1.0f);
    auto sunPos = DateTime::getSunPos() * 100.0f;
    auto pos = glm::vec3(sunPos.x + player.Position.x, sunPos.y + player.Position.y, sunPos.z + player.Position.z);
    float sunSize = 20.0f;
    model = translate(model, pos);
    model = scale(model, glm::vec3(sunSize, sunSize, sunSize));

    sunAndMoonShader->use();
    sunAndMoonShader->setMat4("model", model);
    sunAndMoonShader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    sunAndMoonShader->setVec3("sunCenter", sunPos);
    sunAndMoonShader->setVec3("color", glm::vec3(1.0, 0.9, 0.4));
    sunAndMoonShader->setFloat("sunRadius", 5.0f);
    mesh.draw();
    glClear(GL_DEPTH_BUFFER_BIT);
}

void Renderer::DrawMoon(const Player &player) {
    float offset = DAY_CYCLE / 2;
    float time = std::fmod(glfwGetTime() + offset, DAY_CYCLE) / DAY_CYCLE;

    auto model = glm::mat4(1.0f);
    auto sunPos = DateTime::getSunPos(time) * 100.0f;
    auto pos = glm::vec3(sunPos.x + player.Position.x, sunPos.y + player.Position.y, sunPos.z + player.Position.z);
    float sunSize = 20.0f;
    model = translate(model, pos);
    model = scale(model, glm::vec3(sunSize, sunSize, sunSize));

    sunAndMoonShader->use();
    sunAndMoonShader->setMat4("model", model);
    sunAndMoonShader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    sunAndMoonShader->setVec3("sunCenter", sunPos);
    sunAndMoonShader->setFloat("sunRadius", 5.0f);
    sunAndMoonShader->setVec3("color", glm::vec3(1.0, 1.0, 1.0));
    moon.draw();
    glClear(GL_DEPTH_BUFFER_BIT);
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

void Renderer::UpdateProjection(const Player &player) {
    const glm::mat4 projection = glm::perspective(45.0f, (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT, 0.1f, 1000.0f);
    const glm::mat4 view = player.camera.GetViewMatrix();

    // test
    // glm::vec3 sunPos = glm::vec3(10, 10, 10);
    // float near_plane = 1.0f, far_plane = 1000.0f;
    // auto view = glm::lookAt(sunPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    // glm::mat4 projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    // // glm::mat4 lightSpaceMatrix = lightProjection * lightView;
    // test

    sunAndMoonShader->use();
    sunAndMoonShader->setMat4("projection", projection);
    sunAndMoonShader->setMat4("view", view);

    depthTestShader->use();
    depthTestShader->setMat4("projection", projection);
    depthTestShader->setMat4("view", view);

    instancedShader->use();
    instancedShader->setMat4("projection", projection);
    instancedShader->setMat4("view", view);
    instancedShader->setVec3("viewPos", player.camera.Position);

    const glm::mat4 orthoProjection = glm::ortho(0.0f, 1600.0f, 0.0f, 900.0f, -1.0f, 1.0f);
    uiShader->use();
    uiShader->setMat4("projection", orthoProjection);
}

void Renderer::UpdateLighting() const {
    instancedShader->use();
    instancedShader->setInt("material.diffuse", 0);
    instancedShader->setInt("material.specular", 1);
    instancedShader->setFloat("material.shininess", 32.0f);

    const float ambient = 0.3;
    const auto lightPos = DateTime::getSunPos();

    instancedShader->setVec3("light.direction", -lightPos);
    instancedShader->setVec3("light.ambient", ambient, ambient, ambient);
    instancedShader->setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
    instancedShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

    glm::vec2 uvScale(1.0f / 8, 1.0f / 8);
    instancedShader->setVec2("uvScale", uvScale);
}
