#ifndef INSTANCED_MESH_H
#define INSTANCED_MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Renderer/Texture.h"
#include <GLFW/glfw3.h>

#include "../../engine/World/Chunk.h"

class ChunkMesh {
public:
    unsigned int vbo, instanceVBO, textureVBO; /// Bufory pozycji, instancji i tekstury
    std::vector<glm::mat4> *positions; /// Pozycje ścian
    std::vector<glm::vec2> *textures; /// Tekstury ścian

    unsigned int VAO; /// Bufor łączący VBO
    int chunkX; /// Kordynat X chunku
    int chunkZ; /// Kordynat Z chunku

    /// Tworzy bufory i wektory
    ChunkMesh();

    /// Tworzy bufory i wektory
    /// @param chunkX kordynat X chunku
    /// @param chunkZ kordynat Z chunku
    ChunkMesh(int chunkX, int chunkZ);

    /// Rysuje ściany
    void draw() const;

    /// Aktualizuje bufory pozycji, tekstury
    void updateBuffers() const;
};

#endif
