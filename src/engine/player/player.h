#ifndef PLAYER_H
#define PLAYER_H

#include "../../engine/player/camera.h"

#include <glm/glm.hpp>
#include <iostream>
#include "../constants.h"

const float WALK_SPEED = 3.5f;
const float SPRINT_SPEED = 25.0f;

enum PlayerMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    DOWN,
    UP,
    JUMP,
    SPRINT,
    WALK
};

const glm::vec3 WorldUp(0.0f, 1.0f, 0.0f);

class Player {
public:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.0f);
    Camera camera;

    bool isSprinting = false;

    Player();
    void handlePlayerMove(PlayerMovement direction, float deltaTime);
    void update(float deltaTime);
};

#endif
