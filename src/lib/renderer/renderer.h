#ifndef RENDERER_H
#define RENDERER_H

#include "../../lib/texture/texture.h"
#include "../../lib/map/pair_hash.h"
#include "../../lib/shader/shader.h"
#include "../../lib/player/player.h"
#include "../../lib/chunk/chunk.h"
#include <unordered_map>

#include <vector>

#include "../mesh/chunkMesh.h"
#include "../mesh/mesh.h"

const int RENDER_DISTANCE = 5;

class Renderer {
public:
    Shader *shader;
    Shader *instancedShader;

    Texture *diamondTexture;
    Texture *dirtTexture;

    Texture *bottomTexture;
    Texture *topTexture;
    Texture *leftTexture;
    Texture *rightTexture;
    Texture *backTexture;
    Texture *frontTexture;

    Texture *texturePack;

    std::vector<ChunkMesh> chunkMeshes;

    Player player;

    bool changed = false;

    Renderer(Player &player);

    int chunkX;
    int lastChunkX;
    int chunkZ;
    int lastChunkZ;

    void clear();

    void draw(
        const Player &player,
        const std::unordered_map<std::pair<int, int>, Chunk, PairHash> &chunks);

    void update_shader(const Player &player);

    void update_chunks(
        const std::unordered_map<std::pair<int, int>,
            Chunk, PairHash> &chunks
    );
};

#endif //RENDERER_H
