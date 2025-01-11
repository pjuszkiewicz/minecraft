#ifndef PLAYER_H
#define PLAYER_H

#include "../../lib/Player/Camera.h"

#include <glm/glm.hpp>
#include <iostream>
#include "../Constants.h"

const float MOUSE_SENSITIVITY = 0.1f;
const float WALK_SPEED = 3.5f;
const float SPRINT_SPEED = 25.0f;
const glm::vec3 WORLD_UP(0.0f, 1.0f, 0.0f);

enum PlayerMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    JUMP,
    SPRINT,
    WALK
};

const glm::vec3 WorldUp(0.0f, 1.0f, 0.0f);

class Player {
public:
    glm::vec3 Position;

    glm::vec3 Front;
    glm::vec3 Right;
    glm::vec3 Up;

    float Yaw = -90.0f;
    float Pitch = 0.0f;

    float VelocityY = -0.1f;
    bool IsGrounded = true;
    bool IsSprinting = false;

    Camera camera;

    float lastX = 1600 / 2.0f;
    float lastY = 900 / 2.0f;
    bool firstMouse = true;

    Player(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));

    void handleMouseCallback(double xPosIn, double yPosIn);

    void HandleMouseMove(float xOffset, float yOffset);

    void HandlePlayerMove(PlayerMovement direction, float deltaTime);

    void UpdateVectors();

    void update(float deltaTime);
};

#endif
