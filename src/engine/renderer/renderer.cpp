#include "../../engine/renderer/renderer.h"

#include "geometry/pyramid_geometry.h"
#include "geometry/sphere_geometry.h"


Renderer::Renderer() {
    std::vector<float> sphere = generateSphere(1.0f, 144, 72);
    mesh = new Mesh(&sphere);

    glm::vec3 ambient = glm::vec3(0.25f, 0.25f, 0.25f);
    glm::vec3 diffuse = glm::vec3(0.4, 0.4, 0.4);
    glm::vec3 specular = glm::vec3(0.774597f, 0.774597f, 0.774597f);
    float shininess = 0.6f;
    material = new BasicMaterial(ambient, diffuse, specular, shininess);
}

void Renderer::clear() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::updateProjection(const Player &player) const {
    glm::mat4 projection = glm::perspective(45.0f, (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT, 0.1f, 1000.0f);
    glm::mat4 view = player.camera.getViewMatrix();
    auto model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));

    material->updateProjections(projection, view, model, player.position);
}

void Renderer::draw(const Player &player) {
    clear();
    material->use();
    mesh->draw();
    updateProjection(player);
}