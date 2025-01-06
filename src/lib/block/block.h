#ifndef BLOCK_H
#define BLOCK_H

#include <glm/glm.hpp>

enum BlockType{
    AIR,
    DIRT,
    DIAMOND,
};

class Block{
    public:
        glm::vec3 position;
        BlockType type;

        bool drawTop = false;
        bool drawBottom = false;
        bool drawLeft = false;
        bool drawRight = false;
        bool drawFront = false;
        bool drawBack = false;

        Block() {
            type = AIR;
            position = glm::vec3(0.0f, 0.0f, 0.0f);
        }

        Block(BlockType type) {
            this->type = type;
            position = glm::vec3(0.0f, 0.0f, 0.0f);
        }

        Block(BlockType type, glm::vec3 position) {
            this->type = type;
            this->position = position;
        }
};


#endif