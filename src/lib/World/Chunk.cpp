//
// Created by piotr on 07.01.25.
//

#include "./Chunk.h"

#include <iostream>
#include <ostream>

Block Chunk::getBlock(int x, int y, int z) const {
    return blocks[x][y][z];
}

Block Chunk::getBlock(glm::vec3 pos) const {
    int chunkX = x * CHUNK_WIDTH;
    int chunkZ = z * CHUNK_WIDTH;

    int x = (int) pos.x - chunkX;;
    if (x < 0) x = 0;
    if (x >= CHUNK_WIDTH) x = CHUNK_WIDTH - 1;

    int y = (int) pos.y;
    if (y < 0) y = 0;
    if (y >= CHUNK_HEIGHT) y = CHUNK_HEIGHT - 1;

    int z = (int) pos.z - chunkZ;
    if (z < 0) z = 0;
    if (z >= CHUNK_WIDTH) z = CHUNK_WIDTH - 1;


    return blocks[x][y][z];
}
