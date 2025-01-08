#ifndef INSTANCED_MESH_H
#define INSTANCED_MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#include "../../lib/chunk/chunk.h"

class ChunkMesh {
private:
    unsigned int vbo, instanceVBO;
    std::vector<glm::mat4> *positions;

public:
    unsigned int VAO;
    int chunkX;
    int chunkZ;
    ChunkMesh(int chunkX, int chunkZ);
    void draw() const;
    void setPositions(std::vector<glm::vec3>* positions);
    void updateChunk(const Chunk &chunk);
};

#endif