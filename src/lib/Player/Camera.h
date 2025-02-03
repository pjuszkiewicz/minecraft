#ifndef CAMERA_H
#define CAMERA_H

#include "../../../vendor/glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    /// Pozycja kamery w przestrzeni świata.
    glm::vec3 Position;

    /// Kierunek, w którym kamera patrzy.
    glm::vec3 Front;

    /// Wektor określający, gdzie jest "góra" kamery.
    glm::vec3 Up;

    /// Wektor prostopadły do kierunku patrzenia, wskazujący prawo.
    glm::vec3 Right;

    /// Wektor określający, która strona świata jest uważana za "górę".
    glm::vec3 WorldUp;

    /// Kąt obrotu kamery w poziomie (yaw).
    float Yaw;

    /// Kąt obrotu kamery w pionie (pitch).
    float Pitch;

    /// Prędkość poruszania się kamery.
    float MovementSpeed;

    /// Czułość myszy wpływająca na szybkość obrotu kamery.
    float MouseSensitivity;


    /**
 * @brief Konfiguracja kamery.
 *
 * Inicjalizuje kamerę na podstawie podanej pozycji, wektora określającego "górę" oraz kątów obrotu (yaw i pitch).
 *
 * @param position Pozycja kamery w przestrzeni świata. Domyślnie (0.0f, 0.0f, 0.0f).
 * @param up Wektor określający kierunek "góry" kamery. Domyślnie (0.0f, 1.0f, 0.0f).
 * @param yaw Kąt obrotu kamery w poziomie. Domyślnie -90.0f.
 * @param pitch Kąt obrotu kamery w pionie. Domyślnie 0.0f.
 */
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = -90.0f, float pitch = 0.0f);

    /// Zwraca macierz widoku kamery(na co patrzy)
    glm::mat4 GetViewMatrix() const;

    /// Obraca kamere
    /// @param pitch Kąt obrotu w pionie (pitch).
    /// @param yaw   Kąt obrotu w poziomie (yaw).
    void HandleViewChange(float yaw, float pitch);

    /// Aktualizuje wektory pomocnicze
    void UpdateCameraVectors();

    /// Zwraca kierunek kamery
    glm::vec3 getCameraDirection() const;
};
#endif
