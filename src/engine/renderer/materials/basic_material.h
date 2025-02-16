#ifndef BASIC_MATERIAL_H
#define BASIC_MATERIAL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../shader.h"
#include "../../utils/assets_manager.h"

class BasicMaterial {
public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    Shader *shader;

    BasicMaterial(
        glm::vec3 ambient,
        glm::vec3 diffuse,
        glm::vec3 specular,
        float shininess
    ) : ambient(ambient),
        diffuse(diffuse),
        specular(specular),
        shininess(shininess) {
        shader = new Shader(
            (AssetsManager::getAssetsPath() + "/shaders/basic_material/basic_material.vs").c_str(),
            (AssetsManager::getAssetsPath() + "/shaders/basic_material/basic_material.fs").c_str()
        );
    };

    void updateUniforms() const {
        shader->setVec3("material.ambient", ambient);
        shader->setVec3("material.diffuse", diffuse);
        shader->setVec3("material.specular", specular);
        shader->setFloat("material.shininess", shininess);
    }

    void updateProjections(
        const glm::mat4 &projection,
        const glm::mat4 &view,
        const glm::mat4 &model,
        const glm::vec3 &viewPos
    ) const {
        shader->setMat4("projection", projection);
        shader->setMat4("view", view);
        shader->setMat4("model", model);

        shader->setVec3("viewPos", viewPos);
    }

    void use() const {
        updateUniforms();
        shader->use();
    }
};


#endif //BASIC_MATERIAL_H
