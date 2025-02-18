//
// Created by Piotr Juszkiewicz on 06/01/2025.
//
#include <iostream>
#include "mesh.h"

Mesh::Mesh(std::vector<float> *geometry) {
    // VBO
    // auto geometry = CUBE_GEOMETRY;
    _verticesCount = geometry->size() / 6;

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, geometry->size() * sizeof(float), geometry->data(), GL_STATIC_DRAW);


    // VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);

    // Texture
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));

    // UV
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
}

void Mesh::draw() const {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, _verticesCount);
    glBindVertexArray(0);
}
