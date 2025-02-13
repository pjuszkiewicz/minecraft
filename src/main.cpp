#include "../vendor/glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

#include "engine/Window/Window.h"
#include "engine/Game/Game.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../vendor/stb_image.h"

Game game;

/// Obsługa ruchu myszy
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
    game.player.handleMouseCallback(xposIn, yposIn);
}

int main() {
    try {
        glfwSetInputMode(game.window.glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(game.window.glfwWindow, mouse_callback);
        game.loop();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}