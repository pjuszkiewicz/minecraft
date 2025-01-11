#ifndef INSTANCED_MESH_H
#define INSTANCED_MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Renderer/Texture.h"
#include <GLFW/glfw3.h>

#include "../../lib/World/Chunk.h"

class ChunkMesh {
public:
    unsigned int vbo, instanceVBO, textureVBO, ambientOcclusionVBO;
    std::vector<glm::mat4> *positions;
    std::vector<glm::vec2> *textures;
    std::vector<float> *ambientOcclusions;

    unsigned int VAO;
    int chunkX;
    int chunkZ;
    ChunkMesh();
    ChunkMesh(int chunkX, int chunkZ);
    void draw() const;

    void updateBuffers() const;
    void updateChunk(const Chunk &chunk);
    void updateBlock(const Chunk &chunk, int x, int y, int z);

    void addTopFace(glm::vec3 position);
    void addBottomFace(glm::vec3 position);
    void addLeftFace(glm::vec3 position, bool isTopColliding);
    void addRightFace(glm::vec3 position, bool isTopColliding);
    void addFrontFace(glm::vec3 position, bool isTopColliding);
    void addBackFace(glm::vec3 position, bool isTopColliding);
};

#endif