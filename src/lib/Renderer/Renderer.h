#ifndef RENDERER_H
#define RENDERER_H

#include "../../lib/Renderer/Texture.h"
#include "../../lib/Map/PairHash.h"
#include "../../lib/Renderer/Shader.h"
#include "../../lib/Player/Player.h"
#include "../../lib/World/Chunk.h"
#include <unordered_map>

#include <vector>

#include "ChunkBuilder.h"
#include "Crosshair.h"
#include "../Renderer/ChunkMesh.h"
#include "../Renderer/Mesh.h"
#include "../Constants.h"
#include "../../../vendor/glad/glad.h"

#include <glm/glm.hpp> // Używając GLM dla vec3
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShadowMap.h"

class Renderer {
public:
    Shader *sunAndMoonShader;
    Shader *instancedShader;
    Shader *uiShader;
    Shader *depthShader;
    Shader *depthTestShader;

    ShadowMap shadowMap;

    Mesh mesh;
    Mesh moon;
    Mesh testMesh;

    Texture *texturePack;

    Crosshair *crosshair;

    std::unordered_map<std::pair<int, int>, ChunkMesh, PairHash> chunkMeshes;

    int count = 0;

    bool isReadyToAdd = false;
    std::vector<ChunkBuilder> chunksToAdd;
    std::vector<std::pair<int, int> > chunksToRemove;

    Renderer();

    void Clear();

    void AddChunk();

    void RemoveChunks();

    void Draw(const Player &player, const std::unordered_map<std::pair<int, int>, Chunk, PairHash> &chunks);

    void DrawTestMesh() const;

    void DrawChunks();

    void DrawSun(const Player &player);

    void DrawMoon(const Player &player);

    void UpdateProjection(const Player &player);

    void UpdateLighting() const;
};

#endif //RENDERER_H
