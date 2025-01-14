#ifndef BLOCK_H
#define BLOCK_H

#include <glm/glm.hpp>
#include <map>

enum BlockType {
    AIR,
    DIRT,
    DIAMOND,
    ACACIA_PLANKS,
    ACACIA_WOOD,
    BRICKS,
    STONE,
    AZALEA_LEAVES
};

enum Face {
    FRONT_FACE,
    BACK_FACE,
    LEFT_FACE,
    RIGHT_FACE,
    TOP_FACE,
    BOTTOM_FACE
};

class Block {
public:
    glm::vec3 position;
    BlockType type;

    Block(): position(glm::vec3(0.0f, 0.0f, 0.0f)), type(AIR) {
    }

    Block(BlockType type): type(type), position(glm::vec3(0.0f, 0.0f, 0.0f)) {
    }

    Block(const BlockType type, glm::vec3 position): type(type), position(position) {
    };

    std::pair<int, int> getTextureCoords(Face face = FRONT_FACE, bool isTopColliding = false) {
        if (type == ACACIA_PLANKS) {
            return std::pair<int, int>(3, 8);
        }
        if (type == ACACIA_WOOD) {
            return std::pair<int, int>(4, 8);
        }
                if (type == AZALEA_LEAVES) {
            return std::pair<int, int>(7, 8);
        }
        if (type == STONE) {
            return std::pair<int, int>(6, 8);
        }

        if (type == DIRT) {
            if (face == BOTTOM_FACE) {
                return std::pair<int, int>(0, 8);
            }

            if (face != TOP_FACE) {
                if (isTopColliding) {
                    return std::pair<int, int>(0, 8);
                } else {
                    return std::pair<int, int>(1, 8);
                }
            }
        }
        return std::pair<int, int>(2, 8);
    }
};


#endif
