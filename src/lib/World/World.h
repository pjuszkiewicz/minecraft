#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <unordered_map>
#include "../Chunk/Chunk.h"
#include "../Map/PairHash.h"

class World {
    std::unordered_map<std::pair<int, int>, Chunk, PairHash> chunks;

    bool isBlockAt(glm::vec3 pos);

    void generateChunks();
};

#endif //WORLD_H
