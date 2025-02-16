#ifndef BASIC_MATERIAL_H
#define BASIC_MATERIAL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../shader.h"
#include "../../utils/assets_manager.h"
#include "i_material.h"
#include "../shader_manager.h"

class BasicMaterial : public IMaterial {
public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

    BasicMaterial(
        glm::vec3 ambient,
        glm::vec3 diffuse,
        glm::vec3 specular,
        float shininess
    ) : ambient(ambient),
        diffuse(diffuse),
        specular(specular),
        shininess(shininess) {

        ShaderManager& shaderManager = ShaderManager::getInstance();
        shader = shaderManager.basicShader;
    };

    void updateUniforms() const override{
        shader->setVec3("material.ambient", ambient);
        shader->setVec3("material.diffuse", diffuse);
        shader->setVec3("material.specular", specular);
        shader->setFloat("material.shininess", shininess);
    }
};


#endif //BASIC_MATERIAL_H
