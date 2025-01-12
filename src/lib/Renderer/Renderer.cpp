//
// Created by piotr on 07.01.25.
//

#include "../../lib/Renderer/Renderer.h"
#include <unordered_set>
#include <thread>

Renderer::Renderer() {
    const std::string ASSETS_PATH = "/Users/piotr/Development/C++/minecraft/src/assets";
    // const std::string ASSETS_PATH = "/home/piotr/Development/C++/minecraft/src/assets";

    shader = new Shader((ASSETS_PATH + "/shaders/example/instanced.vs").c_str(),
                        (ASSETS_PATH + "/shaders/example/instanced.fs").c_str());
    instancedShader = new Shader((ASSETS_PATH + "/shaders/example/instanced.vs").c_str(),
                                 (ASSETS_PATH + "/shaders/example/instanced.fs").c_str());
    uiShader = new Shader((ASSETS_PATH + "/shaders/example/ui_vertex.vs").c_str(),
                                 (ASSETS_PATH + "/shaders/example/ui_fragment.fs").c_str());
    texturePack = new Texture((ASSETS_PATH + "/textures/texturepack.png").c_str(), GL_RGBA);
    crosshair = new Crosshair();
}

void Renderer::clear() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(
    const Player &player,
    const std::unordered_map<std::pair<int, int>, Chunk, PairHash> &chunks
) {
    clear();

    update_shader(player);

    add_chunk();
    remove_chunks();
    draw_chunks();

    uiShader->use();
    crosshair->draw();
}

void Renderer::add_chunk() {
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
    // mesh.updateChunk(chunk);
    chunkMeshes[{x, z}] = mesh;
    chunksToAdd.pop_back();
}

void Renderer::remove_chunks() {
    if (chunksToRemove.size() == 0) return;
    auto p = chunksToRemove[chunksToRemove.size() - 1];
    chunkMeshes.erase(p);
    chunksToRemove.pop_back();
}

void Renderer::draw_chunks() {
    texturePack->use(0);
    instancedShader->use();

    for (auto chunkMeshPair: chunkMeshes) {
        ChunkMesh chunkMesh = chunkMeshPair.second;
        chunkMesh.draw();
    }
}

std::vector<glm::vec3> generateUniformSamples(int numSamples) {
    std::vector<glm::vec3> samples;
    for (int i = 0; i < numSamples; i++) {
        float x = static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f;
        float y = static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f;
        float z = static_cast<float>(rand()) / RAND_MAX;
        glm::vec3 sample = glm::normalize(glm::vec3(x, y, z));
        samples.push_back(sample);
    }
    return samples;
}


void Renderer::update_shader(const Player &player) const {
    glm::mat4 projection = glm::perspective(45.0f, (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT, 0.1f, 1000.0f);
    glm::mat4 view = player.camera.GetViewMatrix();

    shader->use();
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);

    instancedShader->use();
    instancedShader->setMat4("projection", projection);
    instancedShader->setMat4("view", view);
    instancedShader->setVec3("viewPos", player.camera.Position);

    glm::vec2 uvScale(1.0f / 8, 1.0f / 8);
    instancedShader->setVec2("uvScale", uvScale);

    glm::vec3 lightPos = glm::normalize(glm::vec3(1.0f, 0.0f, 0.5f));
    instancedShader->setVec3("lightPos", lightPos);

    glm::mat4 orthoProjection = glm::ortho(0.0f, 1600.0f, 0.0f, 900.0f, -1.0f, 1.0f);
    uiShader->use();
    uiShader->setMat4("projection", orthoProjection);
}
