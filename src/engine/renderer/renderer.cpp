#include "../../engine/renderer/renderer.h"

#include "geometry/pyramid_geometry.h"
#include "geometry/sphere_geometry.h"


Renderer::Renderer(std::vector<std::unique_ptr<IGameObject> > &gameObjects) {
    _gameObjects = &gameObjects;
}

void Renderer::clear() {
    glClearColor(0.1f, 0.1f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(const Player &player) {
    glm::mat4 projection = glm::perspective(45.0f, (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT, 0.1f, 1000.0f);
    glm::mat4 view = player.camera.getViewMatrix();

    clear();
    for (auto &gameObject: *_gameObjects) {
        auto model = glm::translate(glm::mat4(1.0f), gameObject->position);
        model = glm::scale(model, gameObject->scale);
        model *= glm::mat4_cast(gameObject->rotation);

        gameObject->material->updateProjections(projection, view, model, player.position);

        glm::vec3 lightPositions[] = {
            player.position,
        };

        glm::vec3 lightColors[] = {
            glm::vec3(100.0f, 100.0f, 100.0f)
        };

        for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i) {
            glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
            newPos = lightPositions[i];
            gameObject->material->shader->setVec3("lightPositions[" + std::to_string(i) + "]", newPos);
            gameObject->material->shader->setVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);
        }
        gameObject->draw();
    }
}
