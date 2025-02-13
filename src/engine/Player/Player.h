#ifndef PLAYER_H
#define PLAYER_H

#include "../../engine/Player/Camera.h"

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
    DOWN,
    UP,
    JUMP,
    SPRINT,
    WALK
};

const glm::vec3 WorldUp(0.0f, 1.0f, 0.0f);

class Player {
public:
    /// Pozycja gracza w przestrzeni świata.
    glm::vec3 Position;

    /// Kierunek, w którym patrzy gracz (kamera).
    glm::vec3 Front;

    /// Wektor prostopadły do kierunku patrzenia, wskazujący prawo.
    glm::vec3 Right;

    /// Wektor określający górę (up) gracza.
    glm::vec3 Up;

    /// Kąt obrotu gracza w poziomie (yaw). Domyślnie -90.0f.
    float Yaw = -90.0f;

    /// Kąt obrotu gracza w pionie (pitch). Domyślnie -90.0f.
    float Pitch = -90.0f;

    /// Prędkość pionowego ruchu gracza (np. wynikająca z grawitacji).
    float VelocityY = -0.1f;

    /// Flaga określająca, czy gracz znajduje się na ziemi.
    bool IsGrounded = true;

    /// Flaga informująca, czy gracz sprintuje.
    bool IsSprinting = false;

    /// Obiekt kamery gracza.
    Camera camera;

    /// Ostatnia znana pozycja kursora myszy w osi X.
    float lastX = 1600 / 2.0f;

    /// Ostatnia znana pozycja kursora myszy w osi Y.
    float lastY = 900 / 2.0f;

    /// Flaga informująca, czy ruch myszy został przetworzony po raz pierwszy.
    bool firstMouse = true;

    /**
     * @brief Konstruktor gracza.
     *
     * Inicjalizuje gracza na zadanej pozycji, ustawiając domyślne wartości dla kamery
     * oraz parametrów ruchu.
     *
     * @param position Pozycja startowa gracza w przestrzeni świata. Domyślnie (0.0f, 128.0f, 0.0f).
     */
    Player(glm::vec3 position = glm::vec3(0.0f, 128.0f, 0.0f));

    /**
     * @brief Obsługuje zdarzenie ruchu myszy.
     *
     * Funkcja przetwarza nowe pozycje kursora myszy i aktualizuje widok kamery.
     *
     * @param xPosIn Aktualna pozycja kursora w osi X.
     * @param yPosIn Aktualna pozycja kursora w osi Y.
     */
    void handleMouseCallback(double xPosIn, double yPosIn);

    /**
     * @brief Obraca kamerę na podstawie przesunięcia myszy.
     *
     * Aktualizuje orientację kamery, wykorzystując przesunięcia kursora w obu osiach.
     *
     * @param xOffset Przesunięcie kursora myszy w osi X.
     * @param yOffset Przesunięcie kursora myszy w osi Y.
     */
    void HandleMouseMove(float xOffset, float yOffset);

    /**
     * @brief Porusza gracza.
     *
     * Przetwarza ruch gracza w określonym kierunku, uwzględniając czas deltaTime.
     *
     * @param direction Kierunek ruchu gracza.
     * @param deltaTime Czas, jaki upłynął od ostatniej aktualizacji (w sekundach).
     */
    void HandlePlayerMove(PlayerMovement direction, float deltaTime);

    /**
     * @brief Aktualizuje wektory pomocnicze kamery.
     *
     * Funkcja oblicza nowe wartości wektorów Front, Right i Up na podstawie bieżących kątów yaw i pitch.
     */
    void UpdateVectors();

    /**
     * @brief Synchronizuje pozycję kamery z pozycją gracza.
     *
     * Aktualizuje położenie kamery, aby podążała za graczem, przy uwzględnieniu czasu deltaTime.
     *
     * @param deltaTime Czas, jaki upłynął od ostatniej aktualizacji (w sekundach).
     */
    void update(float deltaTime);
};

#endif
