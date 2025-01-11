//
// Created by piotr on 11.01.25.
//

#include "./ChunkBuilder.h"

ChunkBuilder::ChunkBuilder(int x, int z) : x(x), z(z) {
    positions = new std::vector<glm::mat4>();
    textures = new std::vector<glm::vec2>();
}

void ChunkBuilder::updateChunk(const Chunk &chunk) {
    this->positions = new std::vector<glm::mat4>();
    this->textures = new std::vector<glm::vec2>();

    for (int x = 0; x < CHUNK_WIDTH; x++) {
        for (int y = 0; y < CHUNK_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_WIDTH; z++) {
                updateBlock(chunk, x, y, z);
            }
        }
    }

    // updateBuffers();
}

void ChunkBuilder::updateBlock(const Chunk &chunk, int x, int y, int z) {
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

    // float ao = calculateAO(isFrontColliding, isLeftColliding, false);
    // ambientOcclusions->push_back(ao);
}

void ChunkBuilder::addLeftFace(glm::vec3 position, bool isTopColliding) {
    auto block = glm::mat4(1.0f);
    block = glm::translate(block, position);
    block = glm::translate(block, glm::vec3(0.0f, 0.0f, 1.0f));
    block = glm::rotate(block, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    block = glm::rotate(block, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    block = glm::rotate(block, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    this->positions->push_back(block);
    int texture = isTopColliding ? 0 : 1;
    glm::vec2 uv = Texture::getUVForBlock(1, texture, 8);
    this->textures->push_back(uv);
}

void ChunkBuilder::addRightFace(glm::vec3 position, bool isTopColliding) {
    auto block = glm::mat4(1.0f);
    block = glm::translate(block, position);
    block = glm::translate(block, glm::vec3(1.0f, 0.0f, 0.0f));
    block = glm::rotate(block, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    block = glm::rotate(block, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    block = glm::rotate(block, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    this->positions->push_back(block);
    int texture = isTopColliding ? 0 : 1;
    glm::vec2 uv = Texture::getUVForBlock(1, texture, 8);
    this->textures->push_back(uv);
}

void ChunkBuilder::addFrontFace(glm::vec3 position, bool isTopColliding) {
    auto block = glm::mat4(1.0f);
    block = glm::translate(block, position);
    this->positions->push_back(block);
    int texture = isTopColliding ? 0 : 1;
    glm::vec2 uv = Texture::getUVForBlock(1, texture, 8);
    this->textures->push_back(uv);
}

void ChunkBuilder::addBackFace(glm::vec3 position, bool isTopColliding) {
    auto block = glm::mat4(1.0f);
    block = glm::translate(block, position);
    block = glm::translate(block, glm::vec3(1.0f, 0.0f, 1.0f));
    block = glm::rotate(block, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    block = glm::rotate(block, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    this->positions->push_back(block);
    int texture = isTopColliding ? 0 : 1;
    glm::vec2 uv = Texture::getUVForBlock(1, texture, 8);
    this->textures->push_back(uv);
}

void ChunkBuilder::addBottomFace(glm::vec3 position) {
    auto block = glm::mat4(1.0f);
    block = glm::translate(block, position);
    block = glm::translate(block, glm::vec3(0.0f, 0.0f, 1.0f));
    block = glm::rotate(block, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
    this->positions->push_back(block);
    glm::vec2 uv = Texture::getUVForBlock(1, 0, 8);
    this->textures->push_back(uv);
}

void ChunkBuilder::addTopFace(glm::vec3 position) {
    auto block = glm::mat4(1.0f);
    block = glm::translate(block, position);
    block = glm::translate(block, glm::vec3(0.0f, 1.0f, 0.0f));
    block = glm::rotate(block, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    this->positions->push_back(block);
    glm::vec2 uv = Texture::getUVForBlock(1, 2, 8);
    this->textures->push_back(uv);
}
