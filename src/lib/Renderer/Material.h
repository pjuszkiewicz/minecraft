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

    virtual void UpdateProjection(glm::mat4 &projection, glm::mat4 &view, const glm::vec3 &pos) = 0;
};


#endif //MATERIAL_H
