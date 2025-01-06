#ifndef VBO_H
#define VBO_H

#include "../../lib/glad/glad.h"

class VBO
{
public:
    GLuint ID;
    VBO(const auto &vertices, const GLsizeiptr size)
    {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, size, &vertices, GL_STATIC_DRAW);
        Unbind();
    }

    void Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, ID);
    }

    void Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    void Delete()
    {
        glDeleteBuffers(1, &ID);
    }
};

#endif