#ifndef RENDERER_H
#define RENDERER_H

#include "../../lib/objects/cube.h"

class Renderer {
public:
    VBO *vbo;
    VAO *vao;
    Shader *shader;

    Renderer() {
        vbo = new VBO(CubeVertices, sizeof(CubeVertices));

        vao = new VAO();
        vao->LinkAttrib(0, 3, GL_FLOAT, 5 * sizeof(float), (void *) (0));
        vao->LinkAttrib(1, 2, GL_FLOAT, 5 * sizeof(float), (void *) (3 * sizeof(float)));

        shader = new Shader("/home/piotr/Development/C++/Minecraft/src/assets/shaders/example/vertex.vs", "/home/piotr/Development/C++/Minecraft/src/assets/shaders/example/fragment.fs");


    }

    ~Renderer() {
        vbo->Delete();
        delete vbo;

        vao->Delete();
        delete vao;
    }

    void clear() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void draw() {
        clear();
    }
};

#endif //RENDERER_H
