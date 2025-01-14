#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <unordered_map>
#include "../World/Chunk.h"
#include "../Map/PairHash.h"

class World {
public:
    std::unordered_map<std::pair<int, int>, Chunk, PairHash> chunks;

    bool isBlockAt(glm::vec3 pos);

    void generateChunks();

    void removeBlockAt(glm::vec3 pos);
    void placeBlockAt(glm::vec3 pos);
    void placeBlockAt(BlockType type, glm::vec3 pos);
};

#endif //WORLD_H
