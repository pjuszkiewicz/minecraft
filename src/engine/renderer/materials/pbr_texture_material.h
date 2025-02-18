#ifndef PBR_TEXTURE_MATERIAL_H
#define PBR_TEXTURE_MATERIAL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../shader.h"
#include "../../utils/assets_manager.h"
#include "i_material.h"
#include "../shader_manager.h"
#include "../texture.h"

class PBRTextureMaterial : public IMaterial {
public:
    Texture *albedo;
    Texture *normal;
    Texture *roughness;
    Texture *metallic;
    Texture *ao;

    PBRTextureMaterial() {
        ShaderManager& shaderManager = ShaderManager::getInstance();
        shader = shaderManager.pbrTextureShader;

        albedo = new Texture((AssetsManager::getAssetsPath() + "/textures/test/albedo.png").c_str(), GL_RGBA);
        normal = new Texture((AssetsManager::getAssetsPath() + "/textures/test/normal.png").c_str(), GL_RGBA);
        roughness = new Texture((AssetsManager::getAssetsPath() + "/textures/test/roughness.png").c_str(), GL_RGBA);
        ao = new Texture((AssetsManager::getAssetsPath() + "/textures/test/ao.png").c_str(), GL_RGBA);
        metallic = new Texture((AssetsManager::getAssetsPath() + "/textures/test/metallic.png").c_str(), GL_RGBA);
    };

    void updateUniforms() const override{
        albedo->use(0);
        normal->use(1);
        roughness->use(2);
        ao->use(3);
        metallic->use(4);
    }
};


#endif //PBR_TEXTURE_MATERIAL_H
