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
    int blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_WIDTH];

    Chunk() {
        x = 0;
        z = 0;
    }

    Chunk(float x, float z) {
        this->x = x;
        this->z = z;
    }
};

#endif