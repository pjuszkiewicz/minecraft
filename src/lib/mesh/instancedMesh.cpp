//
// Created by Piotr Juszkiewicz on 06/01/2025.
//
#include <iostream>

#include "../../lib/glad/glad.h"

#include "../../lib/mesh/mesh.h"
#include "../../lib/objects/cube.h"


InstancedMesh::InstancedMesh() {
    this->positions = new std::vector<glm::vec3>();
    this->faces = new std::vector<uint8_t>();

    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * this->positions->size(), &this->positions->front(),
                 GL_STATIC_DRAW);

    // glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 10000, &positions[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices), CubeVertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));

    // also set instance data
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO); // this attribute comes from a different vertex buffer
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *) 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(2, 1);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices), CubeVertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));

    // also set instance data
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO); // this attribute comes from a different vertex buffer
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // visibility
    // glGenBuffers(1, &visibilityVBO);
    // glBindBuffer(GL_ARRAY_BUFFER, visibilityVBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(uint8_t) * this->faces->size(), &this->faces->front(), GL_STATIC_DRAW);
    //
    // glEnableVertexAttribArray(3); // Atrybut o lokalizacji 2
    // glVertexAttribIPointer(3, 1, GL_UNSIGNED_BYTE, sizeof(uint8_t), (void *) 0);

    glVertexAttribDivisor(2, 1);
    // glVertexAttribDivisor(3, 1);
}

void InstancedMesh::setPositions(std::vector<glm::vec3> *positions) {
    this->positions = positions;

    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * this->positions->size(), &this->positions->front(),
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void InstancedMesh::draw() {
    glBindVertexArray(VAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, this->positions->size());
    glBindVertexArray(0);
}
