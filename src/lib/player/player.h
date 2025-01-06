#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include <iostream>

const float MOUSE_SENSITIVITY = 0.1f;
const float WALK_SPEED = 3.5f;
const float SPRINT_SPEED = 12.0f;
const glm::vec3 WORLD_UP(0.0f, 1.0f, 0.0f);

enum PlayerMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    JUMP,
    SPRINT,
    WALK
};

const glm::vec3 WorldUp(0.0f, 1.0f, 0.0f);

class Player
{
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

    Player(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f))
    {
        Position = position;
        camera = Camera(Position);
    }

    void HandleMouseMove(float xOffset, float yOffset)
    {
        Yaw += xOffset * MOUSE_SENSITIVITY;
        Pitch += yOffset * MOUSE_SENSITIVITY;
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
        camera.HandleViewChange(Yaw, Pitch);
        UpdateVectors();
    }

    void HandlePlayerMove(PlayerMovement direction, float deltaTime)
    {
        if (direction == SPRINT)
            IsSprinting = true;
        if (direction == WALK)
            IsSprinting = false;

        float speed = WALK_SPEED;
        if(IsSprinting) speed = SPRINT_SPEED;

        float velocity = speed * deltaTime;

        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;

        if (direction == JUMP)
        {
            if (IsGrounded)
            {
                VelocityY = 0.15;
            }
            IsGrounded = false;
        }
    }

    void UpdateVectors()
    {
        // glm::vec3 front;
        // front.x = cos(glm::radians(Yaw));
        // front.y = 0;
        // front.z = sin(glm::radians(Yaw));
        // Front = glm::normalize(front);

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

    void update(float deltaTime)
    {
        camera.Position = glm::vec3(Position.x, Position.y + 0.5f, Position.z);
    }
};

#endif
