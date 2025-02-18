#ifndef PBR_MATERIAL_H
#define PBR_MATERIAL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../shader.h"
#include "../../utils/assets_manager.h"
#include "i_material.h"
#include "../shader_manager.h"

class PBRMaterial : public IMaterial {
public:
    glm::vec3 albedo;
    float metallic;
    float roughness;
    float ao;

    PBRMaterial(
        glm::vec3 albedo,
        float metallic,
        float roughness,
        float ao
    ) : albedo(albedo),
        metallic(metallic),
        roughness(roughness),
        ao(ao) {

        ShaderManager& shaderManager = ShaderManager::getInstance();
        shader = shaderManager.pbrShader;
    };

    void updateUniforms() const override{
        shader->setVec3("albedo", albedo);
        shader->setFloat("metallic", metallic);
        shader->setFloat("roughness", roughness);
        shader->setFloat("ao", ao);
    }
};


#endif //PBR_MATERIAL_H
