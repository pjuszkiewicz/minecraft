#ifndef TEXTURE_H
#define TEXTURE_H

#include "../../lib/glad/glad.h"
#include "../../lib/stb_image.h"

class Texture {
public:
    unsigned int ID;

    Texture(const char *path, int format);

    void use(int textureUnit) const;
};

#endif
