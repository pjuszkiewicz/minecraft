#ifndef WINDOW_H
#define WINDOW_H

#include "../../../vendor/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

const int SCR_WIDTH = 1600;
const int SCR_HEIGHT = 900;

class Window {
public:
    /// @brief Wskaźnik na okno GLFW.
    GLFWwindow *glfwWindow;

    /// @brief Wskaźnik na monitor GLFW (używany w trybie pełnoekranowym).
    GLFWmonitor *glfwMonitor;

    /// @brief Wskaźnik na strukturę przechowującą informacje o trybie wideo GLFW.
    const GLFWvidmode *glfwVideoMode;

    /// @brief Flaga określająca, czy okno jest w trybie pełnoekranowym.
    bool isFullscreen = false;

    /**
     * @brief Tworzy okno aplikacji.
     *
     * Inicjalizuje okno GLFW oraz ustawia jego domyślne właściwości.
     */
    Window();

    /**
     * @brief Sprawdza, czy okno powinno zostać zamknięte.
     *
     * @return true jeśli okno powinno zostać zamknięte, false w przeciwnym razie.
     */
    bool shouldClose() const;

    /**
     * @brief Przełącza tryb pełnoekranowy.
     *
     * Jeśli okno jest w trybie okienkowym, przełącza je na pełny ekran.
     * Jeśli jest już w trybie pełnoekranowym, zmienia je na okienkowe.
     */
    void toggleFullscreen();

};

#endif
