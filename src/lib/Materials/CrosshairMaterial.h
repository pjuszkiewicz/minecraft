//
// Created by piotr on 17.01.25.
//

#ifndef CROSSHAIRMATERIAL_H
#define CROSSHAIRMATERIAL_H
#include "../Renderer/Material.h"
#include "../Utils/AssetsManager.h"


class CrosshairMaterial : public Material {
public:
    CrosshairMaterial() {
        std::string path = AssetsManager::GetAssetsPath();
        std::string vertexPath = path + "/shaders/example/ui_vertex.vs";
        std::string fragmentPath = path + "/shaders/example/ui_fragment.fs";
        this->shader = shader = new Shader(vertexPath.c_str(), fragmentPath.c_str());
    }

    void UpdateProjection(glm::mat4 &projection, glm::mat4 &view, const glm::vec3 &pos) override {
        shader->use();
        shader->setMat4("projection", projection);
        shader->setMat4("view", view);
    };
};


#endif //CROSSHAIRMATERIAL_H
