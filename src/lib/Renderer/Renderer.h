#ifndef RENDERER_H
#define RENDERER_H

#include "../../lib/Renderer/Texture.h"
#include "../../lib/Map/PairHash.h"
#include "../../lib/Renderer/Shader.h"
#include "../../lib/Player/Player.h"
#include "../../lib/World/Chunk.h"
#include <unordered_map>

#include <vector>

#include "../Meshes/ChunkBuilder.h"
#include "../Meshes/CrosshairMesh.h"
#include "../Meshes/ChunkMesh.h"
#include "../Meshes/Mesh.h"
#include "../Constants.h"
#include "../../../vendor/glad/glad.h"

#include <glm/glm.hpp> // Używając GLM dla vec3
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Materials/SunAndMoonMaterial.h"

#include "ShadowMap.h"
#include "../GameObjects/SunAndMoon.h"
#include "../Materials/CrosshairMaterial.h"
#include "../Materials/ShadowMappingMaterial.h"
#include "../Materials/WorldMaterial.h"
#include "../Materials/DepthTestMaterial.h"

class Renderer {
public:
    SunAndMoonMaterial sunAndMoonMaterial;
    WorldMaterial worldMaterial;
    CrosshairMaterial crosshairMaterial;
    ShadowMappingMaterial shadowMappingMaterial;
    DepthTestMaterial depthTestMaterial;

    Mesh moon;

    CrosshairMesh *crosshair;

    std::unordered_map<std::pair<int, int>, ChunkMesh, PairHash> chunkMeshes;

    bool isReadyToAdd = false;
    std::vector<ChunkBuilder> chunksToAdd;
    std::vector<std::pair<int, int> > chunksToRemove;

    SunAndMoon sunAndMoon;

    Renderer();

    void Clear();

    void AddChunk();

    void RemoveChunks();

    void Draw(const Player &player);

    void DrawChunks();

    void UpdateProjection(const Player &player) const;
};

#endif //RENDERER_H
