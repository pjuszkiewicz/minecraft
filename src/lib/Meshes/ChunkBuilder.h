//
// Created by piotr on 11.01.25.
//

#ifndef CHUNKBUILDER_H
#define CHUNKBUILDER_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../World/Chunk.h"
#include "../Renderer/Texture.h"

class ChunkBuilder {
public:
    std::vector<glm::mat4> *positions;
    std::vector<glm::vec2> *textures;
    std::vector<float> *ambientOcclusions;

    Chunk chunk;
    Chunk *forward;
    Chunk *back;
    Chunk *left;
    Chunk *right;

    ChunkBuilder(
        const Chunk &chunk,
        Chunk *forward,
        Chunk *back,
        Chunk *left,
        Chunk *right
    ) : chunk(chunk), forward(forward), back(back), left(left), right(right) {

        this->positions = new std::vector<glm::mat4>();
        this->textures = new std::vector<glm::vec2>();
        this->ambientOcclusions = new std::vector<float>();
        updateChunk();
    };

    void updateChunk();

    void updateBlock(
        const Chunk &chunk, int x, int y, int z
    );

    void addTopFace(Block block);

    void addBottomFace(Block block);

    void addLeftFace(Block block, bool isTopColliding) const;

    void addRightFace(Block block, bool isTopColliding) const;

    void addFrontFace(Block block, bool isTopColliding) const;

    void addBackFace(Block block, bool isTopColliding);
};


#endif //CHUNKBUILDER_H
