//
// Created by piotr on 17.01.25.
//

#ifndef SHADOWMAPPINGMATERIAL_H
#define SHADOWMAPPINGMATERIAL_H
#include "../Renderer/Material.h"
#include "../Utils/AssetsManager.h"

class ShadowMappingMaterial : public Material {
public:
    ShadowMappingMaterial() {
        std::string path = AssetsManager::GetAssetsPath();
        std::string vertexPath = path + "/shaders/example/depth.vs";
        std::string fragmentPath = path + "/shaders/example/depth.fs";
        this->shader = shader = new Shader(vertexPath.c_str(), fragmentPath.c_str());
    }
};
#endif //SHADOWMAPPINGMATERIAL_H
