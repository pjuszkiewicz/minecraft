//
// Created by Piotr Juszkiewicz on 09/01/2025.
//

#ifndef TEXTUREPACK_H
#define TEXTUREPACK_H

#include "./Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TexturePack : public Texture {
    public:
    static glm::vec2 getUVForBlock(int blockID, int ui, int vi);
};


#endif //TEXTUREPACK_H
