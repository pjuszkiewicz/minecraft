//
// Created by piotr on 15.01.25.
//

#include "DateTime.h"

#include <cmath>
#include <GLFW/glfw3.h>
#include "./../Constants.h"
#include <iostream>

glm::vec3 rotateAroundAxis(const glm::vec3 &point, float angle, const glm::vec3 &axis) {
    glm::vec3 normalizedAxis = glm::normalize(axis);

    float c = cos(angle);
    float s = sin(angle);

    // Wzór Rodrigueza
    glm::vec3 rotatedPoint = point * c + glm::cross(normalizedAxis, point) * s + normalizedAxis *
                             glm::dot(normalizedAxis, point) * (1.0f - c);

    return rotatedPoint;
}

glm::vec3 circularOrbit(float t, float radius, float angularSpeed, const glm::vec3 &center, const glm::vec3 &normal) {
    float angle = angularSpeed * t;

    float x = radius * cos(angle);
    float y = radius * sin(angle);
    glm::vec3 pointOnCircle = glm::vec3(x, y, 0.0f);

    // Jeśli normalna to {0, 0, 1}, nie potrzeba obrotu
    if (normal == glm::vec3(0, 0, 1)) {
        return center + pointOnCircle;
    }

    // Obróć punkt na okręgu zgodnie z normalą
    glm::vec3 rotatedPoint = rotateAroundAxis(pointOnCircle, acos(glm::dot(glm::vec3(0, 0, 1), glm::normalize(normal))),
                                              glm::cross(glm::vec3(0, 0, 1), glm::normalize(normal)));

    // Dodaj przesunięcie środka
    return center + rotatedPoint;
}

float DateTime::getTime() {
    return std::fmod(glfwGetTime(), DAY_CYCLE) / DAY_CYCLE * 24;
}

/// Oblicza kolor tła na podstawie godziny z glfwGetTime()
/// @return Zwraca wektor z zmiennymi vec3(r, g, b)
glm::vec3 DateTime::getSkyColor() {
    float timeOfDay = DateTime::getTime();
    float r, g, b;
    // 0-12 dzień
    // 12-24 noc

    if (timeOfDay < 3.0f) {
        // Poranek
        float t = timeOfDay / 3.0f;
        r = std::lerp(1, 0.5f, t);
        g = std::lerp(0.63, 0.7f, t);
        b = std::lerp(0.48, 1.0f, t);
    } else if (timeOfDay < 10.0f) {
        // Dzień
        r = 0.5f; // Jasnoniebieskie niebo
        g = 0.7f;
        b = 1.0f;
    } else if (timeOfDay < 13.0f) {
        // Wieczór
        float t = (timeOfDay - 10.0f) / 3.0f;
        r = std::lerp(0.5f, 0.7f, t);
        g = std::lerp(0.7f, 0.3f, t);
        b = std::lerp(1.0f, 0.1f, t);
    } else if (timeOfDay < 14.0f) {
        // Wieczór na noc
        float t = (timeOfDay - 13.0f);
        r = std::lerp(0.7f, 0.05f, t);
        g = std::lerp(0.3f, 0.05f, t);
        b = std::lerp(0.1f, 0.1f, t);
    } else if (timeOfDay < 23.0f) {
        // Noc
        float t = (timeOfDay - 12.0f) / 11.0f;
        r = std::lerp(0.05f, 0.1f, t);
        g = std::lerp(0.05f, 0.1f, t);
        b = std::lerp(0.1f, 0.2f, t);
    } else if (timeOfDay < 24.0f) {
        // Noc
        float t = timeOfDay - 23.0f;
        r = std::lerp(0.1f, 1, t);
        g = std::lerp(0.1f, 0.63, t);
        b = std::lerp(0.2f, 0.48, t);
    }

    return glm::vec3(r, g, b);
}

glm::vec3 DateTime::getSunPos() {
    const float time = getTime() / 24.0f;

    constexpr float angularSpeed = glm::radians(360.0f);
    constexpr auto center = glm::vec3(0.0f);
    constexpr auto normal = glm::vec3(0.0f, 0.0f, 1.0f);
    return glm::normalize(circularOrbit(time, 1, angularSpeed, center, normal));
}

glm::vec3 DateTime::getSunPos(float time) {
    constexpr float angularSpeed = glm::radians(360.0f);
    constexpr auto center = glm::vec3(0.0f);
    constexpr auto normal = glm::vec3(0.0f, 0.0f, 1.0f);
    return glm::normalize(circularOrbit(time, 1, angularSpeed, center, normal));
}