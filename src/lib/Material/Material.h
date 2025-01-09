//
// Created by Piotr Juszkiewicz on 09/01/2025.
//

#ifndef MATERIAL_H
#define MATERIAL_H
#include "../Shader/Shader.h"
#include "../Texture/Texture.h"


class Material {
    Texture* texture;
    Shader* shader;

    Material();
    Material(Texture* texture, Shader* shader);
};


#endif //MATERIAL_H
