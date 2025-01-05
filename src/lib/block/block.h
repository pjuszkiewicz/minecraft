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
        glm::vec3 Position;
        BlockType Type;

        Block() {
            Type = AIR;
            Position = glm::vec3(0.0f, 0.0f, 0.0f);
        }

        Block(BlockType type) {
            Type = type;
            Position = glm::vec3(0.0f, 0.0f, 0.0f);
        }

        Block(BlockType type, glm::vec3 position) {
            Type = type;
            Position = position;
        }
};


#endif