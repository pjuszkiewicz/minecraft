//
// Created by piotr on 17.01.25.
//

#ifndef SUNANDMOONMATERIAL_H
#define SUNANDMOONMATERIAL_H
#include "../../engine/Renderer/Material.h"
#include "../../engine/Constants.h"
#include "../../engine/Utils/AssetsManager.h"


/// Materiał słońca i księżyca
class SunAndMoonMaterial : public Material {
public:
    /// Wczytuje shader
    SunAndMoonMaterial() {
        std::string path = AssetsManager::GetAssetsPath();
        std::string vertexPath = path + "/shaders/example/vertex.vs";
        std::string fragmentPath = path + "/shaders/example/fragment.fs";
        this->shader = shader = new Shader(vertexPath.c_str(), fragmentPath.c_str());
    }

    /// Aktualizuje projekcje
    /// @param projection macierz projekcji
    /// @param view macierz widoku
    /// @param pos wektor pozycji gracza
    void UpdateProjection(glm::mat4 &projection, glm::mat4 &view, const glm::vec3 &pos) override {
        shader->use();
        shader->setMat4("projection", projection);
        shader->setMat4("view", view);
    };
};


#endif //SUNANDMOONMATERIAL_H
