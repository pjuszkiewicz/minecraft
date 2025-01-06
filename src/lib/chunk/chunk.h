#ifndef CHUNK_H
#define CHUNK_H

#include <glm/glm.hpp>
#include "../block/block.h"

const int CHUNK_WIDTH = 32;
const int CHUNK_HEIGHT = 16;

class Chunk{
    public:
    float x;
    float z;
    Block blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_WIDTH];

    Chunk() {
        x = 0;
        z = 0;
    }

    Chunk(float x, float z) {
        this->x = x;
        this->z = z;
    }

    Block getBlock(int x, int y, int z) const {
        return blocks[x][y][z];
    }

    Block getBlock(glm::vec3 pos) const {
        int x = (int) pos.x;
        int y = (int) pos.y;
        int z = (int) pos.z;
        return blocks[x][y][z];
    }
};

#endif