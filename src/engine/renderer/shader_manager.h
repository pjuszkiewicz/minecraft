//
// Created by piotr on 16.02.25.
//

#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include "./materials/basic_material.h"

class ShaderManager {
public:
    Shader *basicShader;
    Shader *pbrShader;
    Shader *pbrTextureShader;

    static ShaderManager &getInstance() {
        static ShaderManager instance;
        return instance;
    }

    ShaderManager() {
        basicShader = new Shader(
            (AssetsManager::getAssetsPath() + "/shaders/basic_shader/basic_shader.vs").c_str(),
            (AssetsManager::getAssetsPath() + "/shaders/basic_shader/basic_shader.fs").c_str()
        );

        pbrShader = new Shader(
            (AssetsManager::getAssetsPath() + "/shaders/pbr_shader/pbr_shader.vs").c_str(),
            (AssetsManager::getAssetsPath() + "/shaders/pbr_shader/pbr_shader.fs").c_str()
        );

        pbrTextureShader = new Shader(
            (AssetsManager::getAssetsPath() + "/shaders/pbr_texture_shader/pbr_texture_shader.vs").c_str(),
            (AssetsManager::getAssetsPath() + "/shaders/pbr_texture_shader/pbr_texture_shader.fs").c_str()
        );
    };
};



#endif //SHADER_MANAGER_H
