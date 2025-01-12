//
// Created by Piotr Juszkiewicz on 11/01/2025.
//

#include "Crosshair.h"
#include <iostream>

#include "../Constants.h"
#include "../../../vendor/glad/glad.h"
#include "../Renderer/Mesh.h"
#include "../Objects/Cube.h"

Crosshair::Crosshair() {
    //    this->vertices = vertices;
    // float vertices[] = {
    //     -0.01f, -0.01f, 0.0f,
    //      0.01f, -0.01f, 0.0f,
    //      -0.01f,  0.01f, 0.0f,
    //
    //     -0.01f, 0.01f, 0.0f,
    //      0.01f, -0.01f, 0.0f,
    //      0.01f,  0.01f, 0.0f,
    // };

        float centerX = SCREEN_WIDTH / 2;
        float centerY = SCREEN_HEIGHT / 2;

        float size = 10;

        float vertices[] = {
            centerX - (size / 2), centerY - (size / 2), 0,
            centerX + (size / 2), centerY + (size / 2), 0,
            centerX - (size / 2), centerY + (size / 2), 0,

            centerX - (size / 2), centerY - (size / 2), 0,
            centerX + (size / 2), centerY - (size / 2), 0,
            centerX + (size / 2), centerY + (size / 2), 0,


        // -0.01f, 0.01f, 0.0f,
        //  0.01f, -0.01f, 0.0f,
        //  0.01f,  0.01f, 0.0f,
    };

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}

void Crosshair::draw() const {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
