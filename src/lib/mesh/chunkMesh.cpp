#include <iostream>

#include "../../lib/glad/glad.h"
#include "./ChunkMesh.h"
#include "../Objects/Cube.h"
#include "../Texture/TexturePack.h"

ChunkMesh::ChunkMesh(int chunkX, int chunkZ) {
    this->chunkX = chunkX;
    this->chunkZ = chunkZ;
    this->positions = new std::vector<glm::mat4>();
    this->textures = new std::vector<glm::vec2>();
    this->ambientOcclusions = new std::vector<float>();

    // INSTANCE VBO
    glGenBuffers(1, &instanceVBO);
    glGenBuffers(1, &textureVBO);
    glGenBuffers(1, &ambientOcclusionVBO);

    // VBO
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices), CubeVertices, GL_STATIC_DRAW);

    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);

    // Texture
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));

    // Instance
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    GLuint location = 2;
    for (int i = 0; i < 4; i++) {
        glEnableVertexAttribArray(location + i);
        glVertexAttribPointer(location + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *) (i * sizeof(glm::vec4)));
        glVertexAttribDivisor(location + i, 1);
    }

    // Texture
    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *) 0);
    glVertexAttribDivisor(6, 1);

    // Ambient occlusion
    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
    glEnableVertexAttribArray(7);
    glVertexAttribPointer(7, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void *) 0);
    glVertexAttribDivisor(7, 1);
}


void ChunkMesh::draw() const {
    if (this->positions->size() != 0) {
        glBindVertexArray(VAO);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, this->positions->size());
        glBindVertexArray(0);
    }
}

float calculateAO(bool side1, bool side2, bool corner) {
    if (side1 && side2) return 0.0f;// Maksymalne zacienienie
    return 1.0f - (side1 + side2 + corner) * 0.25f; // Im więcej sąsiadów, tym ciemniej
}

void ChunkMesh::updateBuffers() const {
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * this->positions->size(), this->positions->data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
    glBufferData(GL_ARRAY_BUFFER, textures->size() * sizeof(glm::vec2), textures->data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, ambientOcclusionVBO);
    glBufferData(GL_ARRAY_BUFFER, ambientOcclusions->size() * sizeof(float), ambientOcclusions->data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ChunkMesh::updateChunk(const Chunk &chunk) {
    this->positions = new std::vector<glm::mat4>();
    this->textures = new std::vector<glm::vec2>();

    for (int x = 0; x < CHUNK_WIDTH; x++) {
        for (int y = 0; y < CHUNK_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_WIDTH; z++) {
                updateBlock(chunk, x, y, z);
            }
        }
    }

    updateBuffers();
}

void ChunkMesh::updateBlock(const Chunk &chunk, int x, int y, int z) {
    if (chunk.blocks[x][y][z].type == BlockType::AIR) {
        return;
    }

    glm::vec3 pos = chunk.blocks[x][y][z].position;

    bool isTopColliding = y != CHUNK_HEIGHT - 1 && chunk.blocks[x][y + 1][z].type != BlockType::AIR;
    if (!isTopColliding) addTopFace(pos);

    bool isBottomColliding = y != 0 && chunk.blocks[x][y - 1][z].type != BlockType::AIR;
    if (!isBottomColliding) addBottomFace(pos);

    bool isLeftColliding = x != 0 && chunk.blocks[x - 1][y][z].type != BlockType::AIR;
    if (!isLeftColliding) addLeftFace(pos, isTopColliding);

    bool isRightColliding = x != CHUNK_WIDTH - 1 && chunk.blocks[x + 1][y][z].type != BlockType::AIR;
    if (!isRightColliding) addRightFace(pos, isTopColliding);

    bool isFrontColliding = z != 0 && chunk.blocks[x][y][z - 1].type != BlockType::AIR;
    if (!isFrontColliding) addFrontFace(pos, isTopColliding);

    bool isBackColliding = z != CHUNK_WIDTH - 1 && chunk.blocks[x][y][z + 1].type != BlockType::AIR;
    if (!isBackColliding) addBackFace(pos, isTopColliding);

    float ao = calculateAO(isFrontColliding, isLeftColliding, false);
    ambientOcclusions->push_back(ao);
}

void ChunkMesh::addLeftFace(glm::vec3 position, bool isTopColliding) {
    auto block = glm::mat4(1.0f);
    block = glm::translate(block, position);
    block = glm::translate(block, glm::vec3(0.0f, 0.0f, 1.0f));
    block = glm::rotate(block, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    block = glm::rotate(block, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    block = glm::rotate(block, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    this->positions->push_back(block);
    int texture = isTopColliding ? 0 : 1;
    glm::vec2 uv = TexturePack::getUVForBlock(1, texture, 8);
    this->textures->push_back(uv);
}

void ChunkMesh::addRightFace(glm::vec3 position, bool isTopColliding) {
    auto block = glm::mat4(1.0f);
    block = glm::translate(block, position);
    block = glm::translate(block, glm::vec3(1.0f, 0.0f, 0.0f));
    block = glm::rotate(block, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    block = glm::rotate(block, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    block = glm::rotate(block, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    this->positions->push_back(block);
    int texture = isTopColliding ? 0 : 1;
    glm::vec2 uv = TexturePack::getUVForBlock(1, texture, 8);
    this->textures->push_back(uv);
}

void ChunkMesh::addFrontFace(glm::vec3 position, bool isTopColliding) {
    auto block = glm::mat4(1.0f);
    block = glm::translate(block, position);
    this->positions->push_back(block);
    int texture = isTopColliding ? 0 : 1;
    glm::vec2 uv = TexturePack::getUVForBlock(1, texture, 8);
    this->textures->push_back(uv);
}

void ChunkMesh::addBackFace(glm::vec3 position, bool isTopColliding) {
    auto block = glm::mat4(1.0f);
    block = glm::translate(block, position);
    block = glm::translate(block, glm::vec3(1.0f, 0.0f, 1.0f));
    block = glm::rotate(block, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    block = glm::rotate(block, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    this->positions->push_back(block);
    int texture = isTopColliding ? 0 : 1;
    glm::vec2 uv = TexturePack::getUVForBlock(1, texture, 8);
    this->textures->push_back(uv);
}

void ChunkMesh::addBottomFace(glm::vec3 position) {
    auto block = glm::mat4(1.0f);
    block = glm::translate(block, position);
    block = glm::translate(block, glm::vec3(0.0f, 0.0f, 1.0f));
    block = glm::rotate(block, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
    this->positions->push_back(block);
    glm::vec2 uv = TexturePack::getUVForBlock(1, 0, 8);
    this->textures->push_back(uv);
}

void ChunkMesh::addTopFace(glm::vec3 position) {
    auto block = glm::mat4(1.0f);
    block = glm::translate(block, position);
    block = glm::translate(block, glm::vec3(0.0f, 1.0f, 0.0f));
    block = glm::rotate(block, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    this->positions->push_back(block);
    glm::vec2 uv = TexturePack::getUVForBlock(1, 2, 8);
    this->textures->push_back(uv);
}
