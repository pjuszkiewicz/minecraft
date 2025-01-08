//
// Created by piotr on 07.01.25.
//

#include "../../lib/renderer/renderer.h"
#include <iostream>
#include "../../lib/objects/cube.h"

Renderer::Renderer(Player &player) {
    chunkX = 0;
    lastChunkX = 0;
    chunkZ = 0;
    lastChunkZ = 0;

    this->player = player;
    const std::string assetsPath = "/Users/piotr/Development/C++/minecraft/src/assets";
    // const std::string assetsPath = "/home/piotr/Development/C++/Minecraft/src/assets";

    shader = new Shader((assetsPath + "/shaders/example/vertex.vs").c_str(),
                        (assetsPath + "/shaders/example/fragment.fs").c_str());

    instancedShader = new Shader((assetsPath + "/shaders/example/instanced.vs").c_str(),
                                 (assetsPath + "/shaders/example/instanced.fs").c_str());

    diamondTexture = new Texture((assetsPath + "/textures/diamond_block.png").c_str(),
                                 GL_RGBA);
    dirtTexture = new Texture((assetsPath + "/textures/dirt.png").c_str(), GL_RGB);

    bottomTexture = new Texture((assetsPath + "/textures/bottom.png").c_str(), GL_RGBA);
    topTexture = new Texture((assetsPath + "/textures/top.png").c_str(), GL_RGBA);
    leftTexture = new Texture((assetsPath + "/textures/left.png").c_str(), GL_RGBA);
    rightTexture = new Texture((assetsPath + "/textures/right.png").c_str(), GL_RGBA);
    backTexture = new Texture((assetsPath + "/textures/back.png").c_str(), GL_RGBA);
    frontTexture = new Texture((assetsPath + "/textures/front.png").c_str(), GL_RGBA);

    texturePack = new Texture((assetsPath + "/textures/texturepack.png").c_str(), GL_RGBA);
}

void Renderer::clear() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(
    const Player &player,
    const std::unordered_map<std::pair<int, int>, Chunk, PairHash> &chunks
) {
    int newChunkX = (player.Position.x - ((int) player.Position.x % CHUNK_WIDTH)) / CHUNK_WIDTH;
    int newChunkZ = (player.Position.z - ((int) player.Position.z % CHUNK_WIDTH)) / CHUNK_WIDTH;

    if (newChunkX != chunkX || newChunkZ != chunkZ) {
        lastChunkX = chunkX;
        chunkX = newChunkX;
        lastChunkZ = chunkZ;
        chunkZ = newChunkZ;

        int dx = chunkX - lastChunkX;
        int dz = chunkZ - lastChunkZ;

        if (dx != 0) {
        }

        update_chunks(chunks);
    }

    clear();
    update_shader(player);

    if (!changed) {
        update_chunks(chunks);
        changed = true;
    }

    diamondTexture->use(0);
    instancedShader->use();

    for (ChunkMesh chunkMesh: chunkMeshes) {
        chunkMesh.draw();
    }
}

void Renderer::update_chunks(
    const std::unordered_map<std::pair<int, int>,
        Chunk, PairHash> &chunks
) {
    // chunkMeshes.clear();

    auto key = chunks.find(std::make_pair(0, 0));

    // int index = 0;
    // for (ChunkMesh chunkMesh: chunkMeshes) {
    for (int i = 0; i < chunkMeshes.size(); i++) {
        if (abs(chunkMeshes[i].chunkX - chunkX) > RENDER_DISTANCE || abs(chunkMeshes[i].chunkZ - chunkZ) > RENDER_DISTANCE) {
            chunkMeshes.erase(chunkMeshes.begin() + i);
            i--;
        }
    }

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

            if (skip) {continue;}



            ChunkMesh chunk = ChunkMesh(x, z);

            key = chunks.find(std::make_pair(x, z));
            if (key != chunks.end()) {
                chunk.updateChunk(key->second);
                chunkMeshes.push_back(chunk);
            }
        }
    }
}

void Renderer::update_shader(const Player &player) {
    const int SCR_WIDTH = 1280;
    const int SCR_HEIGHT = 720;

    glm::mat4 projection = glm::perspective(45.0f, (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = player.camera.GetViewMatrix();

    shader->use();
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);

    instancedShader->use();
    instancedShader->setMat4("projection", projection);
    instancedShader->setMat4("view", view);
}
