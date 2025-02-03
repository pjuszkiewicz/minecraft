//
// Created by Piotr Juszkiewicz on 28/01/2025.
//

#include "WorldObject.h"

#include "../Materials/WorldMaterial.h"

WorldObject::WorldObject() {
    Position = glm::vec3(0, 0, 0);
    Rotation = glm::vec3(0, 0, 0);
    Scale = glm::vec3(1, 1, 1);
    material = new WorldMaterial();
}

void WorldObject::Draw() {
    material->Use(0);

    for (auto chunkMeshPair: chunkMeshes) {
        ChunkMesh chunkMesh = chunkMeshPair.second;
        chunkMesh.draw();
    }

}

void WorldObject::AddChunk() {
    if (chunksToAdd.empty()) return;
    if (!isReadyToAdd) return;

    ChunkBuilder chunk = chunksToAdd[chunksToAdd.size() - 1];
    int x = static_cast<int>(chunk.chunk.x);
    int z = static_cast<int>(chunk.chunk.z);

    auto mesh = ChunkMesh(x, z);
    mesh.positions = chunk.positions;
    mesh.textures = chunk.textures;
    mesh.ambientOcclusions = chunk.ambientOcclusions;
    mesh.updateBuffers();
    chunkMeshes[{x, z}] = mesh;
    chunksToAdd.pop_back();
}

void WorldObject::RemoveChunks() {
    if (chunksToRemove.empty()) return;
    auto p = chunksToRemove[chunksToRemove.size() - 1];
    chunkMeshes.erase(p);
    chunksToRemove.pop_back();
}

void WorldObject::Update() {
    AddChunk();
    RemoveChunks();
}
