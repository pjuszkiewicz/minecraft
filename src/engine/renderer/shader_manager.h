//
// Created by piotr on 16.02.25.
//

#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include "./materials/basic_material.h"

class ShaderManager {
public:
    Shader *basicShader;

    static ShaderManager &getInstance() {
        static ShaderManager instance;
        return instance;
    }

    ShaderManager() {
        basicShader = new Shader(
            (AssetsManager::getAssetsPath() + "/shaders/basic_shader/basic_shader.vs").c_str(),
            (AssetsManager::getAssetsPath() + "/shaders/basic_shader/basic_shader.fs").c_str()
        );
    };
};



#endif //SHADER_MANAGER_H
