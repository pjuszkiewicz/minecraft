//
// Created by piotr on 17.01.25.
//

#ifndef WORLDMATERIAL_H
#define WORLDMATERIAL_H
#include "../Renderer/Material.h"
#include "../Utils/AssetsManager.h"
#include "../Game/DateTime.h"

/// Materiał świata
class WorldMaterial : public Material {
public:
    /// Wczytuje shader i teksture
    WorldMaterial() {
        std::string path = AssetsManager::GetAssetsPath();
        std::string vertexPath = path + "/shaders/example/instanced.vs";
        std::string fragmentPath = path + "/shaders/example/instanced.fs";
        this->shader = shader = new Shader(vertexPath.c_str(), fragmentPath.c_str());

        std::string texturePath = AssetsManager::GetAssetsPath() + "/textures/texturepack.png";
        texture = new Texture(texturePath.c_str(), GL_RGBA);
    }

    /// Aktualizuje projekcje
    /// @param projection macierz projekcji
    /// @param view macierz widoku
    /// @param pos wektor pozycji gracza
    void UpdateProjection(glm::mat4 &projection, glm::mat4 &view, const glm::vec3 &pos) override {
        shader->use();
        shader->setMat4("projection", projection);
        shader->setMat4("view", view);
        shader->setVec3("viewPos", pos);
        glm::vec2 uvScale(1.0f / 8, 1.0f / 8);
        shader->setVec2("uvScale", uvScale);


        const glm::vec3 lightPos = DateTime::getSunPos();
        shader->setVec3("lightPos", lightPos);
    };
};

#endif //WORLDMATERIAL_H
