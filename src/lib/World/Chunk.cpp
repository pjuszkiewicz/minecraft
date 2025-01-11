//
// Created by piotr on 07.01.25.
//

#include "./Chunk.h"

Block Chunk::getBlock(int x, int y, int z) const {
    return blocks[x][y][z];
}

Block Chunk::getBlock(glm::vec3 pos) const {
    int x = (int) pos.x;
    int y = (int) pos.y;
    int z = (int) pos.z;
    return blocks[x][y][z];
}
