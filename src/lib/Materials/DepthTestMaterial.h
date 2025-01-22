//
// Created by piotr on 17.01.25.
//

#ifndef DEPTHTESTMATERIAL_H
#define DEPTHTESTMATERIAL_H
#include "../Renderer/Material.h"
#include "../Utils/AssetsManager.h"


class DepthTestMaterial : public Material {
public:
    DepthTestMaterial() {
        std::string path = AssetsManager::GetAssetsPath();
        std::string vertexPath = path + "/shaders/example/depthTest.vs";
        std::string fragmentPath = path + "/shaders/example/depthTest.fs";
        this->shader = shader = new Shader(vertexPath.c_str(), fragmentPath.c_str());
    }
};


#endif //CROSSHAIRMATERIAL_H
