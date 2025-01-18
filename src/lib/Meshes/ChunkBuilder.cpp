//
// Created by piotr on 11.01.25.
//

#include "ChunkBuilder.h"

// ChunkBuilder::ChunkBuilder(int x, int z) : x(x), z(z) {
//     positions = new std::vector<glm::mat4>();
//     textures = new std::vector<glm::vec2>();
// }

void ChunkBuilder::updateChunk() {
    this->positions = new std::vector<glm::mat4>();
    this->textures = new std::vector<glm::vec2>();
    this->ambientOcclusions = new std::vector<float>();

    for (int x = 0; x < CHUNK_WIDTH; x++) {
        for (int y = 0; y < CHUNK_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_WIDTH; z++) {
                updateBlock(chunk, x, y, z);
            }
        }
    }

    // updateBuffers();
}

float calculateVertexAO(bool side1, bool side2, bool corner) {
    if (side1 && side2) {
        return 0.0f; // Oba boczne bloki zasłaniają – pełne zacienienie
    }
    return 1.0f - (side1 + side2 + corner) * 0.33f;
}

void ChunkBuilder::updateBlock(const Chunk &chunk, int x, int y, int z) {
    if (chunk.blocks[x][y][z].type == BlockType::AIR) {
        return;
    }

    glm::vec3 pos = chunk.blocks[x][y][z].position;

    bool isTopColliding = y != CHUNK_HEIGHT - 1 && chunk.blocks[x][y + 1][z].type != BlockType::AIR;
    if (!isTopColliding) addTopFace(chunk.blocks[x][y][z]);

    bool isBottomColliding = y != 0 && chunk.blocks[x][y - 1][z].type != BlockType::AIR;
    if (!isBottomColliding) addBottomFace(chunk.blocks[x][y][z]);


    bool isLeftColliding = x != 0 && chunk.blocks[x - 1][y][z].type != BlockType::AIR;
    if (x == 0) {
        if (left != nullptr) {
            if (left->blocks[CHUNK_WIDTH - 1][y][z].type != BlockType::AIR) {
                isLeftColliding = true;
            }
        }
    }
    if (!isLeftColliding) addLeftFace(chunk.blocks[x][y][z], isTopColliding);

    bool isRightColliding = x != CHUNK_WIDTH - 1 && chunk.blocks[x + 1][y][z].type != BlockType::AIR;
    if (x == CHUNK_WIDTH - 1) {
        if (right != nullptr) {
            if (right->blocks[0][y][z].type != BlockType::AIR) {
                isRightColliding = true;
            }
        }
    }
    if (!isRightColliding) addRightFace(chunk.blocks[x][y][z], isTopColliding);

    bool isFrontColliding = z != 0 && chunk.blocks[x][y][z - 1].type != BlockType::AIR;
    if (z == 0) {
        if (back != nullptr) {
            if (back->blocks[x][y][CHUNK_WIDTH - 1].type != BlockType::AIR) {
                isFrontColliding = true;
            }
        }
    }
    if (!isFrontColliding) addFrontFace(chunk.blocks[x][y][z], isTopColliding);

    bool isBackColliding = z != CHUNK_WIDTH - 1 && chunk.blocks[x][y][z + 1].type != BlockType::AIR;
    if (z == CHUNK_WIDTH - 1) {
        if (forward != nullptr) {
            if (forward->blocks[x][y][0].type != BlockType::AIR) {
                isBackColliding = true;
            }
        }
    }
    if (!isBackColliding) addBackFace(chunk.blocks[x][y][z], isTopColliding);

    float ao = 1.0;
    // float ao = calculateVertexAO(
    //     chunk.blocks[x][y][z + 1].type == BlockType::AIR,
    //     chunk.blocks[x + 1][y][z].type == BlockType::AIR,
    //     chunk.blocks[x + 1][y][z + 1].type == BlockType::AIR
    // );
    ambientOcclusions->push_back(ao);
}

void ChunkBuilder::addLeftFace(Block block, bool isTopColliding) {
    auto matrix = glm::mat4(1.0f);
    matrix = glm::translate(matrix, block.position);
    matrix = glm::translate(matrix, glm::vec3(0.0f, 0.0f, 1.0f));
    matrix = glm::rotate(matrix, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    matrix = glm::rotate(matrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    this->positions->push_back(matrix);

    int texture = isTopColliding ? 0 : 1;

    auto textureCoords = block.getTextureCoords(LEFT_FACE, isTopColliding);
    glm::vec2 uv = Texture::getUVForBlock(1, textureCoords.first, textureCoords.second);

    // if (block.type == ACACIA_WOOD) {
    //     uv = Texture::getUVForBlock(1, 3, 8);
    // }

    this->textures->push_back(uv);
}

void ChunkBuilder::addRightFace(Block block, bool isTopColliding) {
    auto matrix = glm::mat4(1.0f);
    matrix = glm::translate(matrix, block.position);
    matrix = glm::translate(matrix, glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    this->positions->push_back(matrix);

    // int texture = isTopColliding ? 0 : 1;
    // glm::vec2 uv = Texture::getUVForBlock(1, texture, 8);
    //
    // if (block.type == ACACIA_WOOD) {
    //     uv = Texture::getUVForBlock(1, 3, 8);
    // }

    auto textureCoords = block.getTextureCoords(RIGHT_FACE, isTopColliding);
    glm::vec2 uv = Texture::getUVForBlock(1, textureCoords.first, textureCoords.second);

    this->textures->push_back(uv);
}

void ChunkBuilder::addFrontFace(Block block, bool isTopColliding) {
    auto matrix = glm::mat4(1.0f);
    matrix = glm::translate(matrix, block.position);
    this->positions->push_back(matrix);
    // int texture = isTopColliding ? 0 : 1;
    // glm::vec2 uv = Texture::getUVForBlock(1, texture, 8);
    //
    // if (block.type == ACACIA_WOOD) {
    //     uv = Texture::getUVForBlock(1, 3, 8);
    // }


    auto textureCoords = block.getTextureCoords(FRONT_FACE, isTopColliding);
    glm::vec2 uv = Texture::getUVForBlock(1, textureCoords.first, textureCoords.second);


    this->textures->push_back(uv);
}

void ChunkBuilder::addBackFace(Block block, bool isTopColliding) {
    auto matrix = glm::mat4(1.0f);
    matrix = glm::translate(matrix, block.position);
    matrix = glm::translate(matrix, glm::vec3(1.0f, 0.0f, 1.0f));
    matrix = glm::rotate(matrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    this->positions->push_back(matrix);
    // int texture = isTopColliding ? 0 : 1;
    // glm::vec2 uv = Texture::getUVForBlock(1, texture, 8);
    // if (block.type == ACACIA_WOOD) {
    //     uv = Texture::getUVForBlock(1, 3, 8);
    // }


    auto textureCoords = block.getTextureCoords(BACK_FACE, isTopColliding);
    glm::vec2 uv = Texture::getUVForBlock(1, textureCoords.first, textureCoords.second);


    this->textures->push_back(uv);
}

void ChunkBuilder::addBottomFace(Block block) {
    auto matrix = glm::mat4(1.0f);
    matrix = glm::translate(matrix, block.position);
    matrix = glm::translate(matrix, glm::vec3(0.0f, 0.0f, 1.0f));
    matrix = glm::rotate(matrix, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
    this->positions->push_back(matrix);
    // glm::vec2 uv = Texture::getUVForBlock(1, 0, 8);
    // if (block.type == ACACIA_WOOD) {
    //     uv = Texture::getUVForBlock(1, 3, 8);
    // }

    auto textureCoords = block.getTextureCoords(BOTTOM_FACE);
    glm::vec2 uv = Texture::getUVForBlock(1, textureCoords.first, textureCoords.second);


    this->textures->push_back(uv);
}

void ChunkBuilder::addTopFace(Block block) {
    auto matrix = glm::mat4(1.0f);
    matrix = glm::translate(matrix, block.position);
    matrix = glm::translate(matrix, glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    this->positions->push_back(matrix);
    // glm::vec2 uv = Texture::getUVForBlock(1, 2, 8);
    // if (block.type == ACACIA_WOOD) {
    //     uv = Texture::getUVForBlock(1, 3, 8);
    // }


    auto textureCoords = block.getTextureCoords(TOP_FACE);
    glm::vec2 uv = Texture::getUVForBlock(1, textureCoords.first, textureCoords.second);


    this->textures->push_back(uv);
}
