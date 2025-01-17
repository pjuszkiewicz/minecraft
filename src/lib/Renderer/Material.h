//
// Created by piotr on 17.01.25.
//

#ifndef MATERIAL_H
#define MATERIAL_H
#include "Shader.h"
#include "Texture.h"


class Material {
public:
    Shader *shader;
    Texture *texture;

    Material();

    Material(Shader *shader, Texture *texture);

    void Use(int textureUnit);
};


#endif //MATERIAL_H
