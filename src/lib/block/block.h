#ifndef BLOCK_H
#define BLOCK_H

#include <glm/glm.hpp>

class Block{
    public:
        glm::vec3 Position;
        Block() {
            Position = glm::vec3(0.0f, 0.0f, 0.0f);
        }

        Block(glm::vec3 position) {
            Position = position;
        }
};


#endif