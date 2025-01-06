#ifndef VAO_H
#define VAO_H

#include "../../lib/glad/glad.h"

class VAO{
    public:
    GLuint ID;    
    VAO() {
        glGenVertexArrays(1, &ID);
    }

    void LinkAttrib(
        GLuint layout,
        GLuint numComponents,
        GLenum type,
        GLsizeiptr stride,
        void* offset
    ) {
        Bind();
        glEnableVertexAttribArray(layout);
        glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
        Unbind();
    }

    void Bind() {
        glBindVertexArray(ID);
    }

    void Unbind() {
        glBindVertexArray(0);
    }

    void Delete() {
        glDeleteVertexArrays(1, &ID);
    }
};

#endif