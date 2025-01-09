//
// Created by piotr on 07.01.25.
//

#include "../../lib/Renderer/Renderer.h"


Renderer::Renderer(Player &player) {
    std::string ASSETS_PATH = "/Users/piotr/Development/C++/minecraft/src/assets";
    // const std::string ASSETS_PATH = "/home/piotr/Development/C++/Minecraft/src/assets";

    chunkX = 0;
    lastChunkX = 0;
    chunkZ = 0;
    lastChunkZ = 0;

    this->player = player;

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

        update_chunks(chunks);
    }

    clear();
    update_shader(player);

    if (!changed) {
        update_chunks(chunks);
        changed = true;
    }

    texturePack->use(0);
    instancedShader->use();

    for (ChunkMesh chunkMesh: chunkMeshes) {
        chunkMesh.draw();
    }
}

void Renderer::update_chunks(
    const std::unordered_map<std::pair<int, int>,
        Chunk, PairHash> &chunks
) {
    std::cout << "Chunk Meshes count: " << chunkMeshes.size() << std::endl;
    std::cout << "Update chunks: " << glfwGetTime() << std::endl;

    auto key = chunks.find(std::make_pair(0, 0));

    std::vector<int> chunkMeshesToReuse;

    // Usuwanie chunków
    for (int i = 0; i < chunkMeshes.size(); i++) {
        if (abs(chunkMeshes[i].chunkX - chunkX) > RENDER_DISTANCE || abs(chunkMeshes[i].chunkZ - chunkZ) >
            RENDER_DISTANCE) {
            // chunkMeshes.erase(chunkMeshes.begin() + i);
            // i--;
            chunkMeshesToReuse.push_back(i);
        }
    }

    std::cout << "Delete chunks: " << glfwGetTime() << std::endl;

    // Dodanie nowych
    for (int i = -RENDER_DISTANCE; i <= RENDER_DISTANCE; i++) {
        for (int j = -RENDER_DISTANCE; j <= RENDER_DISTANCE; j++) {
            int x = chunkX + i;
            int z = chunkZ + j;

            bool skip = false;

            for (ChunkMesh chunkMesh: chunkMeshes) {
                if (chunkMesh.chunkX == x && chunkMesh.chunkZ == z) {
                    skip = true;
                }
            }

            if (skip) { continue; }

            key = chunks.find(std::make_pair(x, z));
            if (key != chunks.end()) {
                if (chunkMeshesToReuse.size() > 0) {
                    chunkMeshes[chunkMeshesToReuse[0]].updateChunk(key->second);
                    chunkMeshesToReuse.erase(chunkMeshesToReuse.begin());
                } else {
                    ChunkMesh chunk = ChunkMesh(x, z);
                    chunk.updateChunk(key->second);
                    chunkMeshes.push_back(chunk);
                }
            }
        }
    }

    std::cout << "update chunks: " << glfwGetTime() << std::endl;
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
