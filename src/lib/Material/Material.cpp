//
// Created by Piotr Juszkiewicz on 09/01/2025.
//

#include "./Material.h"
#include "../Constants.h"

Material::Material() {
    shader = new Shader((ASSETS_PATH + "/shaders/example/vertex.vs").c_str(),
                        (ASSETS_PATH + "/shaders/example/fragment.fs").c_str());
}


Material::Material(Texture *texture, Shader *shader) {
    this->texture = texture;
    this->shader = shader;
}
