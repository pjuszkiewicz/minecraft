//
// Created by Piotr Juszkiewicz on 28/01/2025.
//

#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <unordered_map>
#include "../../engine/Game/IGameObject.h"
#include "../../engine/Map/PairHash.h"
#include "../../engine/Meshes/ChunkMesh.h"
#include "../../engine/Meshes/ChunkBuilder.h"

class ChunkBuilder;
class ChunkMesh;

/// GameObject świata gry
class WorldObject : public IGameObject {
public:
    std::unordered_map<std::pair<int, int>, ChunkMesh, PairHash> chunkMeshes; /// Mapa aktualnie renderowanych meshy
    bool isReadyToAdd = false; /// Czy można aktualnie dodać mesha do renderu
    std::vector<ChunkBuilder> chunksToAdd; /// Meshe do dodania
    std::vector<std::pair<int, int> > chunksToRemove; /// Meshes do usunięcia

    /// Initializuje pozycje mesh i materiał
    WorldObject();

    ~WorldObject() override {
    }

    /// Rysuje objekt
    void Draw() override;

    /// Dodaje i usuwa chunk w jeden klatce
    void Update() override;

    /// Dodaje chunk do renderowania
    void AddChunk();

    /// Usuwa chunk z renderowania
    void RemoveChunks();
};


#endif //WORLDOBJECT_H
