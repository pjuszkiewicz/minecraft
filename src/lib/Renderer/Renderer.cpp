#include "../../lib/Renderer/Renderer.h"
#include <unordered_set>
#include <thread>

#include "Material.h"
#include "../Game/DateTime.h"
#include "../Window/Window.h"

Renderer::Renderer() {
}

/// Czyści ekran kolorem z DateTime::getSkyColor()
void Renderer::Clear() {
    glm::vec3 color = DateTime::getSkyColor();
    glClearColor(color.x, color.y, color.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/// Aktualizuje projekcje i rysuje objekty
void Renderer::Draw(const Player &player) {
    UpdateProjection(player);
    Clear();
    sunAndMoon.Draw();
    worldObject.Draw();
    worldObject.Update();
    crosshairObject.Draw();
}

/// Aktualizuje projekcje na podstawie pozycji i rotacji kamery
void Renderer::UpdateProjection(const Player &player) const {
    glm::mat4 projection = glm::perspective(45.0f, (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT, 0.1f, 1000.0f);
    glm::mat4 view = player.camera.GetViewMatrix();

    worldObject.material->UpdateProjection(projection, view, player.camera.Position);
    sunAndMoon.material->UpdateProjection(projection, view, player.camera.Position);


    const glm::mat4 orthoProjection = glm::ortho(0.0f, 1600.0f, 0.0f, 900.0f, -1.0f, 1.0f);
    crosshairObject.material->shader->use();
    crosshairObject.material->shader->setMat4("projection", orthoProjection);
}
