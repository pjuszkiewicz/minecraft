#include <iostream>

#include "../../../vendor/glad/glad.h"
#include "../Meshes/ChunkMesh.h"
#include "../Objects/Plane.h"

ChunkMesh::ChunkMesh() {
    ChunkMesh(0, 0);
}

ChunkMesh::ChunkMesh(int chunkX, int chunkZ) {
    this->chunkX = chunkX;
    this->chunkZ = chunkZ;
    this->positions = new std::vector<glm::mat4>();
    this->textures = new std::vector<glm::vec2>();
    this->normals = new std::vector<glm::vec3>();
    this->ambientOcclusions = new std::vector<float>();

    // INSTANCE VBO
    glGenBuffers(1, &instanceVBO);
    glGenBuffers(1, &textureVBO);
    glGenBuffers(1, &ambientOcclusionVBO);
    glGenBuffers(1, &normalVBO);

    // VBO
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(PlaneVertices), PlaneVertices, GL_STATIC_DRAW);

    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);

    // Texture
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));

    // // Normals
    glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
    glEnableVertexAttribArray(8);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
    glVertexAttribPointer(8, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) (3 * sizeof(float)));
    glVertexAttribDivisor(8, 1);

    // Instance
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    GLuint location = 2;
    for (int i = 0; i < 4; i++) {
        glEnableVertexAttribArray(location + i);
        glVertexAttribPointer(location + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *) (i * sizeof(glm::vec4)));
        glVertexAttribDivisor(location + i, 1);
    }

    // Texture
    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *) 0);
    glVertexAttribDivisor(6, 1);

    // Ambient occlusion
    glBindBuffer(GL_ARRAY_BUFFER, ambientOcclusionVBO);
    glEnableVertexAttribArray(7);
    glVertexAttribPointer(7, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void *) 0);
    glVertexAttribDivisor(7, 1);
}


void ChunkMesh::draw() const {
    if (this->positions->size() != 0) {
        glBindVertexArray(VAO);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, this->positions->size());
        glBindVertexArray(0);
    }
}

float calculateAO(bool side1, bool side2, bool corner) {
    if (side1 && side2) return 0.0f; // Maksymalne zacienienie
    return 1.0f - (side1 + side2 + corner) * 0.25f; // Im więcej sąsiadów, tym ciemniej
}

void ChunkMesh::updateBuffers() const {
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * this->positions->size(), this->positions->data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
    glBufferData(GL_ARRAY_BUFFER, textures->size() * sizeof(glm::vec2), textures->data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, ambientOcclusionVBO);
    glBufferData(GL_ARRAY_BUFFER, ambientOcclusions->size() * sizeof(float), ambientOcclusions->data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
    glBufferData(GL_ARRAY_BUFFER, normals->size() * sizeof(float), normals->data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
