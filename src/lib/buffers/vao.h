#ifndef VAO_H
#define VAO_H

#include "../../lib/glad/glad.h"
#include "vbo.h"

class VAO {
public:
    GLuint ID;

    /**
     * Tworzy Vertex Array Object
     */
    VAO();

    /**
     * Ustawia wskaźniki atrybutów dla bufora
     *
     * Pokazuje karcie graficznej jak ma obsłużyć dane podane w VBO
     * @param vbo referencja VBO dla którego ustawiamy wskaźniki
     * @param layout index danych w vertex shaderze
     * @param size rozmiar danych (np. dla vec3 wybieramy 3)
     * @param type typ danych (z reguły GL_FLOAT)
     * @param stride rozmiar jednego rzędu danych
     * @param offset odstęp pod którym zaczyna się wartośćw rzędzie
     */
    void LinkVBO(VBO *vbo, GLuint layout, GLint size, GLenum type, GLsizei stride, const void *offset);

    /**
     * Binduje VAO
     */
    void Bind() const;

    /**
     * Unbinduje VAO
     */
    void Unbind();

    /**
     * Usuwa VAO
     */
    void Delete();
};

#endif
