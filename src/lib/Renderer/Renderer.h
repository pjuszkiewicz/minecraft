#ifndef RENDERER_H
#define RENDERER_H

#include "../../lib/Texture/Texture.h"
#include "../../lib/Map/PairHash.h"
#include "../../lib/Shader/Shader.h"
#include "../../lib/Player/Player.h"
#include "../../lib/Chunk/Chunk.h"
#include <unordered_map>

#include <vector>

#include "../Mesh/ChunkMesh.h"
#include "../Mesh/Mesh.h"
#include "../Constants.h"

const int RENDER_DISTANCE = 5;

class Renderer {
public:
    Shader *shader;
    Shader *instancedShader;

    Texture *texturePack;

    std::unordered_map<std::pair<int, int>, ChunkMesh, PairHash> chunkMeshes;

    bool changed = false;

    int chunkX;
    int lastChunkX;
    int chunkZ;
    int lastChunkZ;

    Renderer();

    void clear();

    void draw(
        const Player &player,
        const std::unordered_map<std::pair<int, int>, Chunk, PairHash> &chunks);

    void update_shader(const Player &player);

    void update_initial_chunks(
        const std::unordered_map<std::pair<int, int>,
            Chunk, PairHash> &chunks
    );

    void update_chunks(
        const std::unordered_map<std::pair<int, int>,
            Chunk, PairHash> &chunks
    );
};

#endif //RENDERER_H
