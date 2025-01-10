//
// Created by piotr on 07.01.25.
//

#include "../../lib/Renderer/Renderer.h"
#include <unordered_set>
#include <thread>

Renderer::Renderer() {
    std::string ASSETS_PATH = "/Users/piotr/Development/C++/minecraft/src/assets";
    // const std::string ASSETS_PATH = "/home/piotr/Development/C++/Minecraft/src/assets";

    chunkX = 0;
    lastChunkX = 0;
    chunkZ = 0;
    lastChunkZ = 0;

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
    int newChunkX = (player.Position.x - (static_cast<int>(player.Position.x) % CHUNK_WIDTH)) / CHUNK_WIDTH;
    int newChunkZ = (player.Position.z - (static_cast<int>(player.Position.z) % CHUNK_WIDTH)) / CHUNK_WIDTH;

    if (newChunkX != chunkX || newChunkZ != chunkZ) {
        lastChunkX = chunkX;
        chunkX = newChunkX;
        lastChunkZ = chunkZ;
        chunkZ = newChunkZ;

        // std::thread t(update_chunks, chunks);
        // std::thread t([this, chunks]() { update_chunks(chunks); });
        // auto bound_function = std::bind(&Renderer::update_chunks, this, std::ref(chunks));

        // Przekazanie związanej funkcji do std::thread
        // std::thread t(bound_function);

        // update_chunks(chunks);
        // t.join();
    }

    clear();
    update_shader(player);

    if (!changed) {
        update_initial_chunks(chunks);
        changed = true;
    }

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

    for (int i = -RENDER_DISTANCE; i <= RENDER_DISTANCE; i++) {
        for (int j = -RENDER_DISTANCE; j <= RENDER_DISTANCE; j++) {
            int x = chunkX + i;
            int z = chunkZ + j;

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
                // chunkMeshes.push_back(chunk);
                chunkMeshes[{x, z}] = chunk;
            }
        }
    }
}

void Renderer::update_chunks(
    const std::unordered_map<std::pair<int, int>, Chunk, PairHash> &chunks
) {
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
            // chunkMeshes.erase(chunkMeshPair.first);
            // chunkMeshes.erase(chunkMeshes.begin() + i);
            // i--;
            // chunkMeshesToReuse.push_back(i);
            auto pair = std::make_pair(chunkMesh.chunkX, chunkMesh.chunkZ);
            chunkMeshesToReuse.push_back(pair);
        }
    }

    // for (int i = 0; i < chunkMeshes.size(); i++) {
    //     if (abs(chunkMeshes[i].chunkX - chunkX) > RENDER_DISTANCE || abs(chunkMeshes[i].chunkZ - chunkZ) >
    //         RENDER_DISTANCE) {
    //         // chunkMeshes.erase(chunkMeshes.begin() + i);
    //         // i--;
    //         chunkMeshesToReuse.push_back(i);
    //     }
    // }

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
                    // ChunkMesh chunk = ChunkMesh(x, z);
                    // chunk.updateChunk(key->second);
                    // chunkMeshes.push_back(chunk);
                }
            }
        }
    }

    std::cout << "update chunks: " << glfwGetTime() << ", " << testCount << std::endl;
}

void Renderer::update_shader(const Player &player) {
    const int SCR_WIDTH = 1600;
    const int SCR_HEIGHT = 900;

    glm::mat4 projection = glm::perspective(45.0f, (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 1000.0f);
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
