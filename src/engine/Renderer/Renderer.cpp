#include "../../engine/Renderer/Renderer.h"
#include <unordered_set>
#include <thread>

#include "Material.h"
#include "../Game/DateTime.h"
#include "../Window/Window.h"

Renderer::Renderer() {
}

void Renderer::Clear() {
    glm::vec3 color = DateTime::getSkyColor();
    glClearColor(color.x, color.y, color.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const Player &player) {
    Clear();
    UpdateProjection(player);
    sunAndMoon.Draw();
    worldObject.Draw();
    worldObject.Update();
    crosshairObject.Draw();
}

void Renderer::UpdateProjection(const Player &player) const {
    glm::mat4 projection = glm::perspective(45.0f, (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT, 0.1f, 1000.0f);
    glm::mat4 view = player.camera.GetViewMatrix();

    worldObject.material->UpdateProjection(projection, view, player.camera.Position);
    sunAndMoon.material->UpdateProjection(projection, view, player.camera.Position);

    /// Projekcja celownika
    const glm::mat4 orthoProjection = glm::ortho(0.0f, 1600.0f, 0.0f, 900.0f, -1.0f, 1.0f);
    crosshairObject.material->shader->use();
    crosshairObject.material->shader->setMat4("projection", orthoProjection);
}
