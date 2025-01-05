#ifndef CHUNK_H
#define CHUNK_H

#include <glm/glm.hpp>
#include "../block/block.h"

const int CHUNK_WIDTH = 16;
const int CHUNK_HEIGHT = 16;

class Chunk{
    public:
    float PosX;
    float PosZ;
    Block blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_WIDTH];

    Chunk() {
        PosX = 0;
        PosZ = 0;
    }

    Chunk(float x, float z) {
        PosX = x;
        PosZ = z;
    }
};

#endif