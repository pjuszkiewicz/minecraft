//
// Created by piotr on 17.01.25.
//

#ifndef WORLDMATERIAL_H
#define WORLDMATERIAL_H
#include "../Renderer/Material.h"
#include "../Utils/AssetsManager.h"

class WorldMaterial : public Material {
public:
    WorldMaterial() {
        std::string path = AssetsManager::GetAssetsPath();
        std::string vertexPath = path + "/shaders/example/instanced.vs";
        std::string fragmentPath = path + "/shaders/example/instanced.fs";
        this->shader = shader = new Shader(vertexPath.c_str(), fragmentPath.c_str());

        std::string texturePath = AssetsManager::GetAssetsPath() + "/textures/texturepack.png";
        texture = new Texture(texturePath.c_str(), GL_RGBA);
    }
};

#endif //WORLDMATERIAL_H
