#include "../../engine/renderer/renderer.h"

#include "geometry/pyramid_geometry.h"
#include "geometry/sphere_geometry.h"


Renderer::Renderer(std::vector<std::unique_ptr<IGameObject>> &gameObjects) {
     _gameObjects = &gameObjects;
}

void Renderer::clear() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// void Renderer::updateProjection(const Player &player) const {
//     glm::mat4 projection = glm::perspective(45.0f, (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT, 0.1f, 1000.0f);
//     glm::mat4 view = player.camera.getViewMatrix();
//
//     for (auto gameObject : *_gameObjects) {
//         auto model = glm::translate(glm::mat4(1.0f), gameObject->position);
//
//         gameObject->material->updateProjections(projection, view, model, player.position);
//     }
// }

void Renderer::draw(const Player &player) {
    glm::mat4 projection = glm::perspective(45.0f, (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT, 0.1f, 1000.0f);
    glm::mat4 view = player.camera.getViewMatrix();

    clear();
    for (auto &gameObject : *_gameObjects) {
        auto model = glm::translate(glm::mat4(1.0f), gameObject->position);

        gameObject->material->updateProjections(projection, view, model, player.position);
        gameObject->draw();
    }
}