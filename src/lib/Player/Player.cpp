//
// Created by piotr on 07.01.25.
//

#include "../../lib/Player/Player.h"

Player::Player(glm::vec3 position) {
    Position = position;
    camera = Camera(Position);

    camera.HandleViewChange(Yaw, Pitch);
    UpdateVectors();
}

void Player::handleMouseCallback(double xPosIn, double yPosIn) {
    float xpos = static_cast<float>(xPosIn);
    float ypos = static_cast<float>(yPosIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    HandleMouseMove(xoffset, yoffset);
}

void Player::HandleMouseMove(float xOffset, float yOffset) {
    Yaw += xOffset * MOUSE_SENSITIVITY;
    Pitch += yOffset * MOUSE_SENSITIVITY;
    if (Pitch > 89.0f)
        Pitch = 89.0f;
    if (Pitch < -89.0f)
        Pitch = -89.0f;
    camera.HandleViewChange(Yaw, Pitch);
    UpdateVectors();
}

void Player::HandlePlayerMove(PlayerMovement direction, float deltaTime) {
    if (direction == SPRINT)
        IsSprinting = true;
    if (direction == WALK)
        IsSprinting = false;

    float speed = WALK_SPEED;
    if (IsSprinting) speed = SPRINT_SPEED;

    float velocity = speed * deltaTime;

    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;

    if (direction == JUMP) {
        if (IsGrounded) {
            VelocityY = 0.15;
        }
        IsGrounded = false;
    }
}

void Player::UpdateVectors() {
    // glm::vec3 front;
    // front.x = cos(glm::radians(Yaw));
    // front.y = 0;
    // front.z = sin(glm::radians(Yaw));
    // Front = glm::normalize(front);
    //
    // Right = glm::normalize(glm::cross(Front, WORLD_UP));
    // Up = glm::normalize(glm::cross(Right, Front));

    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}

void Player::update(float deltaTime) {
    camera.Position = glm::vec3(Position.x, Position.y + 0.5f, Position.z);
}
