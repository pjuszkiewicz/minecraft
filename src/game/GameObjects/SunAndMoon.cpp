//
// Created by Piotr Juszkiewicz on 17/01/2025.
//

#include "SunAndMoon.h"

#include "../../engine/Game/DateTime.h"

SunAndMoon::SunAndMoon() {
    Position = glm::vec3(0, 0, 0);
    Rotation = glm::vec3(0, 0, 0);
    Scale = glm::vec3(1, 1, 1);
    material = new SunAndMoonMaterial();
}

void SunAndMoon::Draw() {
    float sunSize = 20.0f;

    auto model = glm::mat4(1.0f);
    auto sunPos = DateTime::getSunPos() * 100.0f;
    auto pos = glm::vec3(sunPos.x + Position.x, sunPos.y + Position.y, sunPos.z + Position.z);
    auto lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    auto color = glm::vec3(1.0, 0.9, 0.4);

    model = translate(model, pos);
    model = scale(model, glm::vec3(sunSize, sunSize, sunSize));

    material->shader->use();
    material->shader->setMat4("model", model);
    material->shader->setVec3("lightColor", lightColor);
    material->shader->setVec3("color", color);
    material->shader->setVec3("sunCenter", sunPos);
    material->shader->setFloat("sunRadius", 5.0f);
    mesh.draw();

    // Moon
    float offset = DAY_CYCLE / 2;
    float time = std::fmod(glfwGetTime() + offset, DAY_CYCLE) / DAY_CYCLE;

    model = glm::mat4(1.0f);
    sunPos = DateTime::getSunPos(time) * 100.0f;
    pos = glm::vec3(sunPos.x + Position.x, sunPos.y + Position.y, sunPos.z + Position.z);
    sunSize = 20.0f;
    model = translate(model, pos);
    model = scale(model, glm::vec3(sunSize, sunSize, sunSize));

    material->shader->setMat4("model", model);
    material->shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    material->shader->setVec3("sunCenter", sunPos);
    material->shader->setFloat("sunRadius", 5.0f);
    material->shader->setVec3("color", glm::vec3(1.0, 1.0, 1.0));
    mesh.draw();
    glClear(GL_DEPTH_BUFFER_BIT);
}

