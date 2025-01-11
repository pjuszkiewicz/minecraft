#ifndef VBO_H
#define VBO_H

#include "../../lib/glad/glad.h"

/**
 * Menedżer Vertex Buffer Object
 */
class VBO {
public:
    unsigned int ID;
    /**
     * Tworzy Vertex Buffer Object i przesyła do niego dane z parametry vertices
     *
     * VBO dalej zostaje zbindowane po utworzeniu
     * @param data Array wartości VBO
     */
    VBO(const auto *data) ;

    /**
     * Binduje VBO
     */
    void Bind() const ;

    /**
    * Unbinduje VBO
    */
    void Unbind() ;

    /**
    * Usuwa VBO
    */
    void Delete() const;
};

#endif
