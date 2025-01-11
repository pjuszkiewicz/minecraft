#include "../vendor/glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

#include "lib/Window/Window.h"
#include "lib/Game/Game.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../vendor/stb_image.h"

Game game;

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
    game.player.handleMouseCallback(xposIn, yposIn);
}

int main() {
    glfwSetInputMode(game.window.glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(game.window.glfwWindow, mouse_callback);
    game.loop();
    return 0;
}