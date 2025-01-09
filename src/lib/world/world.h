//
// Created by Piotr Juszkiewicz on 08/01/2025.
//

#ifndef WORLD_H
#define WORLD_H

#include <vector>

class World {
    std::vector<std::vector<int> > generateTerrain(int worldWidth, int chunkHeight, float scale);
};


#endif //WORLD_H
