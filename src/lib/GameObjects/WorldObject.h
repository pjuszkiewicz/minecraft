//
// Created by Piotr Juszkiewicz on 28/01/2025.
//

#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <unordered_map>
#include "../Game/GameObject.h"
#include "../../lib/Map/PairHash.h"
#include "../Meshes/ChunkMesh.h"
#include "../Meshes/ChunkBuilder.h"

class ChunkBuilder;
class ChunkMesh;

class WorldObject : public GameObject {
public:
    std::unordered_map<std::pair<int, int>, ChunkMesh, PairHash> chunkMeshes;
    bool isReadyToAdd = false;
    std::vector<ChunkBuilder> chunksToAdd;
    std::vector<std::pair<int, int> > chunksToRemove;

    WorldObject();

    void AddChunk();

    void RemoveChunks();

    void Draw() override;

    void Update();
};


#endif //WORLDOBJECT_H
