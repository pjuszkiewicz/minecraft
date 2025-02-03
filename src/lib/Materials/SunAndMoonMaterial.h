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

    void UpdateProjection(glm::mat4 &projection, glm::mat4 &view, const glm::vec3 &pos) override {
        shader->use();
        shader->setMat4("projection", projection);
        shader->setMat4("view", view);
    };
};


#endif //SUNANDMOONMATERIAL_H
