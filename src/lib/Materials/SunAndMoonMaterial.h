//
// Created by piotr on 17.01.25.
//

#ifndef SUNANDMOONMATERIAL_H
#define SUNANDMOONMATERIAL_H
#include "../Renderer/Material.h"
#include "../Constants.h"
#include "../Utils/AssetsManager.h"


class SunAndMoonMaterial : public Material {
public:
    SunAndMoonMaterial() {
        std::string path = AssetsManager::GetAssetsPath();
        std::string vertexPath = path + "/shaders/example/vertex.vs";
        std::string fragmentPath = path + "/shaders/example/fragment.fs";
        this->shader = shader = new Shader(vertexPath.c_str(), fragmentPath.c_str());
    }
};


#endif //SUNANDMOONMATERIAL_H
