#ifndef CAMERA_H
#define CAMERA_H

#include "../../../vendor/glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const float MOUSE_SENSITIVITY = 0.1f;
const glm::vec3 WORLD_UP(0.0f, 1.0f, 0.0f);

class Camera {
public:
    glm::vec3 *position;
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    float yaw = -90.0f;
    float pitch = 0.0f;

    bool isFirstMouse = true;

    float lastX = 1600 / 2.0f;
    float lastY = 900 / 2.0f;

    Camera(glm::vec3 &position);

    glm::mat4 getViewMatrix() const;

    glm::vec3 getCameraDirection() const;

    void handleMouseCallback(double xPosIn, double yPosIn);

    void updateCameraVectors();
};
#endif
