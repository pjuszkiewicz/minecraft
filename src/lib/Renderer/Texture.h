#ifndef TEXTURE_H
#define TEXTURE_H

#include "../../../vendor/glad/glad.h"
#include "../../../vendor/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Texture {
public:
    unsigned int ID;

    Texture(const char *path, int format);

    void use(int textureUnit) const;

    static glm::vec2 getUVForBlock(int blockID, int ui, int vi);
};

#endif
