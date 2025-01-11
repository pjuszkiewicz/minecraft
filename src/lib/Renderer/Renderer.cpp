//
// Created by piotr on 07.01.25.
//

#include "../../lib/Renderer/Renderer.h"
#include <unordered_set>
#include <thread>

Renderer::Renderer() {
    // const std::string ASSETS_PATH = "/Users/piotr/Development/C++/minecraft/src/assets";
    const std::string ASSETS_PATH = "/home/piotr/Development/C++/minecraft/src/assets";

    shader = new Shader((ASSETS_PATH + "/shaders/example/instanced.vs").c_str(),
                        (ASSETS_PATH + "/shaders/example/instanced.fs").c_str());

    instancedShader = new Shader((ASSETS_PATH + "/shaders/example/instanced.vs").c_str(),
                                 (ASSETS_PATH + "/shaders/example/instanced.fs").c_str());

    texturePack = new Texture((ASSETS_PATH + "/textures/texturepack.png").c_str(), GL_RGBA);
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

    if (!changed) {
        update_initial_chunks(chunks);
        changed = true;
    }

    draw_chunks(player, chunks);
}

void Renderer::draw_chunks(
    const Player &player,
    const std::unordered_map<std::pair<int, int>, Chunk, PairHash> &chunks
) {
    texturePack->use(0);
    instancedShader->use();

    for (auto chunkMeshPair: chunkMeshes) {
        ChunkMesh chunkMesh = chunkMeshPair.second;
        chunkMesh.draw();
    }
}

void Renderer::update_initial_chunks(
    const std::unordered_map<std::pair<int, int>,
        Chunk, PairHash> &chunks
) {
    auto key = chunks.find(std::make_pair(0, 0));

    for (int x = -RENDER_DISTANCE; x <= RENDER_DISTANCE; x++) {
        for (int z = -RENDER_DISTANCE; z <= RENDER_DISTANCE; z++) {
            bool skip = false;

            for (auto chunkMeshPair: chunkMeshes) {
                ChunkMesh chunkMesh = chunkMeshPair.second;
                if (chunkMesh.chunkX == x && chunkMesh.chunkZ == z) {
                    skip = true;
                }
            }

            if (skip) { continue; }

            key = chunks.find(std::make_pair(x, z));
            if (key != chunks.end()) {
                auto chunk = ChunkMesh(x, z);
                chunk.updateChunk(key->second);
                // chunkMeshes.push_back(Chunk);
                chunkMeshes[{x, z}] = chunk;
            }
        }
    }
}

void Renderer::update_chunks(
    const std::unordered_map<std::pair<int, int>, Chunk, PairHash> &chunks
) {
    int chunkX = 0;
    int chunkZ = 0;
    std::cout << std::endl;
    std::cout << "Chunk Meshes count: " << chunkMeshes.size() << std::endl;
    std::cout << "Update chunks: " << glfwGetTime() << std::endl;

    auto key = chunks.find(std::make_pair(0, 0));

    std::vector<std::pair<int, int> > chunkMeshesToReuse;

    std::unordered_set<std::pair<int, int>, PairHash> loadedChunks;
    for (auto chunkMeshPair: chunkMeshes) {
        ChunkMesh chunkMesh = chunkMeshPair.second;
        loadedChunks.insert(std::make_pair(chunkMesh.chunkX, chunkMesh.chunkZ));
    }

    // Usuwanie chunków
    for (auto chunkMeshPair: chunkMeshes) {
        ChunkMesh chunkMesh = chunkMeshPair.second;

        if (abs(chunkMesh.chunkX - chunkX) > RENDER_DISTANCE || abs(chunkMesh.chunkZ - chunkZ) > RENDER_DISTANCE) {
            auto pair = std::make_pair(chunkMesh.chunkX, chunkMesh.chunkZ);
            chunkMeshesToReuse.push_back(pair);
        }
    }

    std::cout << "Delete chunks: " << glfwGetTime() << std::endl;
    std::cout << "chunksRemoved: " << chunkMeshesToReuse.size() << std::endl;

    int testCount = 0;

    // // Dodanie nowych
    for (int i = -RENDER_DISTANCE; i <= RENDER_DISTANCE; i++) {
        for (int j = -RENDER_DISTANCE; j <= RENDER_DISTANCE; j++) {
            int x = chunkX + i;
            int z = chunkZ + j;

            // auto pair = std::make_pair(x, z);

            auto key = std::make_pair(x, z);

            auto foundChunkMesh = chunkMeshes.find(key);
            if (foundChunkMesh != chunkMeshes.end()) {
                continue;
            }

            auto foundChunk = chunks.find(key);
            if (foundChunk != chunks.end()) {
                ChunkMesh chunkMesh = ChunkMesh(x, z);
                chunkMesh.updateChunk(foundChunk->second);
                chunkMeshes[key] = chunkMesh;
            }

            testCount++;

            if (foundChunk != chunks.end()) {
                if (chunkMeshesToReuse.size() > 0) {
                    // chunkMeshes[chunkMeshesToReuse.back()].updateChunk(foundChunk->second);
                    // chunkMeshes[chunkMeshesToReuse.back()].chunkX = foundChunk->second.x;
                    // chunkMeshes[chunkMeshesToReuse.back()].chunkZ = foundChunk->second.z;
                    // chunkMeshesToReuse.pop_back();
                } else {
                    // ChunkMesh Chunk = ChunkMesh(x, z);
                    // Chunk.updateChunk(key->second);
                    // chunkMeshes.push_back(Chunk);
                }
            }
        }
    }

    std::cout << "update chunks: " << glfwGetTime() << ", " << testCount << std::endl;
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

    glm::vec2 uvScale(1.0f / 8, 1.0f / 8);
    instancedShader->setVec2("uvScale", uvScale);

    glm::vec3 lightDirection = glm::normalize(glm::vec3(1.0f, -0.5f, 0.5f));
    instancedShader->setVec3("lightDirection", lightDirection);
}
