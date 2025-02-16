//
// Created by piotr on 07.01.25.
//

#include "../player/camera.h"

#include <iostream>
#include <ostream>

Camera::Camera(glm::vec3 &pos) {
    this->position = &pos;
    updateCameraVectors();
}

glm::vec3 Camera::getCameraDirection() const {
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    return glm::normalize(direction);
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(*position, *position + front, up);
}

void Camera::handleMouseCallback(double xPosIn, double yPosIn) {
    std::cout << position->x << " " << position->y << " " << position->z << std::endl;
    float xpos = static_cast<float>(xPosIn);
    float ypos = static_cast<float>(yPosIn);

    if (isFirstMouse) {
        lastX = xpos;
        lastY = ypos;
        isFirstMouse = false;
    }

    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    yaw += xOffset * MOUSE_SENSITIVITY;
    pitch += yOffset * MOUSE_SENSITIVITY;
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, WORLD_UP));
    up = glm::normalize(glm::cross(right, front));
}