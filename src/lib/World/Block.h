#ifndef BLOCK_H
#define BLOCK_H

#include <glm/glm.hpp>

enum BlockType {
    AIR,
    DIRT,
    DIAMOND,
    ACACIA_PLANKS,
    ACACIA_WOOD,
    BRICKS
};

class Block {
public:
    glm::vec3 position;
    BlockType type;

    Block(): position(glm::vec3(0.0f, 0.0f, 0.0f)), type(AIR) {
    }

    Block(BlockType type): type(type), position(glm::vec3(0.0f, 0.0f, 0.0f)) {
    }

    Block(BlockType type, glm::vec3 position): type(type), position(position) {
    };

    std::pair<int, int> getTextureCoords() {
        if (type == ACACIA_WOOD) {
            return std::pair<int, int>(3, 8);
        }
        return std::pair<int, int>(2, 8);
    }
};


#endif
