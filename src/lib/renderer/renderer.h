#ifndef RENDERER_H
#define RENDERER_H

#include "../../lib/texture/texture.h"
#include "../../lib/map/pair_hash.h"
#include "../../lib/shader/shader.h"
#include "../../lib/player/player.h"
#include "../../lib/chunk/chunk.h"
#include <unordered_map>

#include <vector>

#include "../mesh/mesh.h"

const int RENDER_DISTANCE = 4;



class Renderer {
public:
    Shader *shader;

    Texture *diamondTexture;
    Texture *dirtTexture;

    Texture *bottomTexture;
    Texture *topTexture;
    Texture *leftTexture;
    Texture *rightTexture;
    Texture *backTexture;
    Texture *frontTexture;

    Texture *texturePack;

    Mesh *mesh;

    bool changed = false;


    Renderer();

    void clear();

    void draw(Player *player, const std::unordered_map<std::pair<int, int>, Chunk, PairHash> &chunks);

    void update_shader(Player *player);

    void draw_new_chunks(const std::unordered_map<std::pair<int, int>, Chunk, PairHash> &chunks, Player *player) const;

    void draw_chunk(const std::unordered_map<std::pair<int, int>, Chunk, PairHash> &chunks, const Chunk &chunk) const;
};

#endif //RENDERER_H
