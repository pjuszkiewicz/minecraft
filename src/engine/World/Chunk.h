#ifndef CHUNK_H
#define CHUNK_H

#include <glm/glm.hpp>
#include "../World/Block.h"

const int CHUNK_WIDTH = 16;
const int CHUNK_HEIGHT = 128;

/// @brief Klasa reprezentująca pojedynczy chunk w świecie gry.
class Chunk {
public:
    /// @brief Pozycja chunku w świecie (współrzędne X i Z).
    float x;
    float z;

    /// @brief Tablica przechowująca bloki w chunku.
    Block blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_WIDTH];

    /// @brief Konstruktor domyślny inicjalizujący chunk na pozycji (0,0).
    Chunk() : x(0), z(0) {
    }

    /// @brief Konstruktor inicjalizujący chunk na określonych współrzędnych.
    /// @param x Współrzędna X chunku.
    /// @param z Współrzędna Z chunku.
    Chunk(float x, float z) : x(x), z(z) {
    }

    /**
     * @brief Zwraca blok na podanych współrzędnych w chunku.
     *
     * @param x Współrzędna X bloku w chunku.
     * @param y Współrzędna Y bloku w chunku.
     * @param z Współrzędna Z bloku w chunku.
     * @return Block Blok znajdujący się na podanej pozycji.
     */
    Block getBlock(int x, int y, int z) const;

    /**
     * @brief Zwraca blok na podstawie wektora pozycji w chunku.
     *
     * @param pos Wektor pozycji bloku w chunku.
     * @return Block Blok znajdujący się na podanej pozycji.
     */
    Block getBlock(glm::vec3 pos) const;
};


#endif
