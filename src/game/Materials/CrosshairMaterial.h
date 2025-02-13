//
// Created by piotr on 17.01.25.
//

#ifndef CROSSHAIRMATERIAL_H
#define CROSSHAIRMATERIAL_H
#include "../../engine/Renderer/Material.h"
#include "../../engine/Utils/AssetsManager.h"


/// Materiał celownika
class CrosshairMaterial : public Material {
public:
    /// Wczytuje shader
    CrosshairMaterial() {
        std::string path = AssetsManager::GetAssetsPath();
        std::string vertexPath = path + "/shaders/example/ui_vertex.vs";
        std::string fragmentPath = path + "/shaders/example/ui_fragment.fs";
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


#endif //CROSSHAIRMATERIAL_H
