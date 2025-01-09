#ifndef CHUNK_H
#define CHUNK_H

#include <glm/glm.hpp>
#include "../block/block.h"

const int CHUNK_WIDTH = 16;
const int CHUNK_HEIGHT = 64;

class Chunk {
public:
    float x;
    float z;
    Block blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_WIDTH];

    Chunk(): x(0), z(0) {
    }

    Chunk(float x, float z): x(x), z(z) {
    }


    Block getBlock(int x, int y, int z) const;

    Block getBlock(glm::vec3 pos) const;
};

#endif
