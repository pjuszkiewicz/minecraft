#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <unordered_map>
#include "../World/Chunk.h"
#include "../Map/PairHash.h"

/// @brief Klasa reprezentująca świat gry, przechowująca chunki i operacje na blokach.
class World {
public:
    /// @brief Mapa przechowująca chunki w świecie, indeksowana parą współrzędnych (X, Z).
    std::unordered_map<std::pair<int, int>, Chunk, PairHash> chunks;

    BlockType currentBlock = STONE;

    /**
     * @brief Sprawdza, czy na podanej pozycji znajduje się blok.
     *
     * @param pos Wektor pozycji w świecie.
     * @return true Jeśli na danej pozycji znajduje się blok.
     * @return false Jeśli na danej pozycji nie ma bloku.
     */
    bool isBlockAt(glm::vec3 pos);

    /**
     * @brief Generuje początkowe chunki świata.
     */
    void generateChunks();

    /**
     * @brief Usuwa blok znajdujący się na podanej pozycji.
     *
     * @param pos Wektor pozycji bloku do usunięcia.
     */
    void removeBlockAt(glm::vec3 pos);

    /**
     * @brief Kładzie domyślny blok na podanej pozycji.
     *
     * @param pos Wektor pozycji, na której ma zostać postawiony blok.
     */
    void placeBlockAt(glm::vec3 pos);

    /**
     * @brief Kładzie blok określonego typu na podanej pozycji.
     *
     * @param type Typ bloku, który ma zostać postawiony.
     * @param pos Wektor pozycji, na której ma zostać postawiony blok.
     */
    void placeBlockAt(BlockType type, glm::vec3 pos);
};


#endif //WORLD_H
