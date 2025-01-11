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
        updateChunk();
    };

    void updateChunk();

    void updateBlock(
        const Chunk &chunk, int x, int y, int z
    );

    void addTopFace(glm::vec3 position);

    void addBottomFace(glm::vec3 position);

    void addLeftFace(glm::vec3 position, bool isTopColliding);

    void addRightFace(glm::vec3 position, bool isTopColliding);

    void addFrontFace(glm::vec3 position, bool isTopColliding);

    void addBackFace(glm::vec3 position, bool isTopColliding);
};


#endif //CHUNKBUILDER_H
