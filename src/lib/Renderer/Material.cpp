//
// Created by piotr on 17.01.25.
//

#include "Material.h"

Material::Material() {
    shader = nullptr;
    texture = nullptr;
}

Material::Material(Shader *shader, Texture *texture) {
    this->shader = shader;
    this->texture = texture;
}

void Material::Use(int textureUnit) {
    if (this->shader != nullptr) {
        this->shader->use();
    }
    if (this->texture != nullptr) {
        this->texture->use(textureUnit);
    }
}
