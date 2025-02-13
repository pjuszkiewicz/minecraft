//
// Created by Piotr Juszkiewicz on 11/01/2025.
//

#include "CrosshairMesh.h"
#include <iostream>

#include "../Constants.h"
#include "../../../vendor/glad/glad.h"
#include "../Meshes/Mesh.h"
#include "../Objects/Cube.h"

CrosshairMesh::CrosshairMesh() {
    float centerX = SCREEN_WIDTH / 2;
    float centerY = SCREEN_HEIGHT / 2;

    float size = 2;

    float vertices[] = {
        centerX - (size / 2), centerY - (size / 2), 0,
        centerX + (size / 2), centerY + (size / 2), 0,
        centerX - (size / 2), centerY + (size / 2), 0,

        centerX - (size / 2), centerY - (size / 2), 0,
        centerX + (size / 2), centerY - (size / 2), 0,
        centerX + (size / 2), centerY + (size / 2), 0,
    };

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
}

void CrosshairMesh::draw() const {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
