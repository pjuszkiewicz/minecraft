#ifndef RENDERER_H
#define RENDERER_H

#include "../../lib/Renderer/Texture.h"
#include "../../lib/Map/PairHash.h"
#include "../../lib/Renderer/Shader.h"
#include "../../lib/Player/Player.h"
#include "../../lib/World/Chunk.h"
#include <unordered_map>

#include <vector>

#include "../Renderer/ChunkMesh.h"
#include "../Renderer/Mesh.h"
#include "../Constants.h"

const int RENDER_DISTANCE = 5;

class Renderer {
public:
    Shader *shader;
    Shader *instancedShader;

    Texture *texturePack;

    std::unordered_map<std::pair<int, int>, ChunkMesh, PairHash> chunkMeshes;

    bool changed = false;

    int count = 0;

    std::vector<Chunk> chunksToRender;

    Renderer();

    void clear();

    void draw(
        const Player &player,
        const std::unordered_map<std::pair<int, int>, Chunk, PairHash> &chunks);

    void draw_chunks(
        const Player &player,
        const std::unordered_map<std::pair<int, int>, Chunk, PairHash> &chunks);

    void update_shader(const Player &player) const;

    void update_initial_chunks(
        const std::unordered_map<std::pair<int, int>,
            Chunk, PairHash> &chunks
    );

    void add_chunk();

    void update_chunks(
        const std::unordered_map<std::pair<int, int>,
            Chunk, PairHash> &chunks
    );
};

#endif //RENDERER_H
