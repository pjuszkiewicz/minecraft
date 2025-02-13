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

/// @brief Klasa reprezentująca pojedynczy blok w świecie gry.
class Block {
public:
    /// @brief Pozycja bloku w świecie.
    glm::vec3 position;

    /// @brief Typ bloku (np. STONE, DIRT, WOOD).
    BlockType type;

    /// @brief Konstruktor domyślny inicjalizujący blok jako powietrze.
    Block() : position(glm::vec3(0.0f, 0.0f, 0.0f)), type(AIR) {
    }

    /// @brief Konstruktor inicjalizujący blok z określonym typem.
    /// @param type Typ bloku.
    Block(BlockType type) : type(type), position(glm::vec3(0.0f, 0.0f, 0.0f)) {
    }

    /// @brief Konstruktor inicjalizujący blok z określoną pozycją i typem.
    /// @param type Typ bloku.
    /// @param position Pozycja bloku w świecie.
    Block(const BlockType type, glm::vec3 position) : type(type), position(position) {
    }

    /**
     * @brief Zwraca współrzędne tekstury w atlasie tekstur.
     *
     * @param face Strona bloku, dla której pobierana jest tekstura (np. FRONT_FACE).
     * @param isTopColliding Określa, czy na górze znajduje się inny blok (używane np. dla brudu).
     * @return std::pair<int, int> Współrzędne tekstury w atlasie.
     */
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
