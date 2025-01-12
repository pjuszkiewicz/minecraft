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

class Renderer {
public:
    Shader *shader;
    Shader *instancedShader;
    Shader *uiShader;

    Texture *texturePack;

    Crosshair *crosshair;

    std::unordered_map<std::pair<int, int>, ChunkMesh, PairHash> chunkMeshes;

    int count = 0;

    bool isReadyToAdd = false;
    std::vector<ChunkBuilder> chunksToAdd;
    std::vector<std::pair<int, int>> chunksToRemove;

    Renderer();

    void clear();

    void draw(
        const Player &player,
        const std::unordered_map<std::pair<int, int>, Chunk, PairHash> &chunks);

    void draw_chunks();

    void update_shader(const Player &player) const;

    void add_chunk();
    void remove_chunks();

};

#endif //RENDERER_H
