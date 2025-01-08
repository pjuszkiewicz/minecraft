//
// Created by Piotr Juszkiewicz on 07/01/2025.
//

#include <iostream>
#include "vao.h"

VAO::VAO() {
    glGenVertexArrays(1, &ID);
}

void VAO::LinkVBO(VBO *vbo, GLuint layout, GLint size, GLenum type, GLsizei stride, const void *offset) {
    // this->Bind();
    vbo->Bind();
    glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    vbo->Unbind();
    this->Unbind();
}

void VAO::Bind() const {
    glBindVertexArray(ID);
}

void VAO::Unbind() {
    glBindVertexArray(0);
}

void VAO::Delete() {
    glDeleteVertexArrays(1, &ID);
}
