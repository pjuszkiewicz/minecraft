#ifndef BLOCK_H
#define BLOCK_H

#include <glm/glm.hpp>

class Block{
    public:
        Block(glm::vec3 position) {
            Position = position;
        }

        glm::vec3 Position;
};


#endif