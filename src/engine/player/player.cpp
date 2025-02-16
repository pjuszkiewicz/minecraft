//
// Created by piotr on 07.01.25.
//

#include "../../engine/player/player.h"

Player::Player() : camera(Camera(position)) {
}

void Player::handlePlayerMove(PlayerMovement direction, float deltaTime) {
    if (direction == SPRINT)
        isSprinting = true;
    if (direction == WALK)
        isSprinting = false;

    float speed = WALK_SPEED;
    if (isSprinting) speed = SPRINT_SPEED;

    float velocity = speed * deltaTime;

    if (direction == FORWARD)
        position += camera.front * velocity;
    if (direction == BACKWARD)
        position -= camera.front * velocity;
    if (direction == LEFT)
        position -= camera.right * velocity;
    if (direction == RIGHT)
        position += camera.right * velocity;

    if (direction == UP)
        position += camera.up * velocity;
    if (direction == DOWN)
        position -= camera.up * velocity;
}

void Player::update(float deltaTime) {
}
