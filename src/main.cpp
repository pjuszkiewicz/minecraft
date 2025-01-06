#include "lib/glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>

#include "lib/shader/shader.h"
#include "lib/texture/texture.h"
#include "lib/camera/camera.h"
#include "lib/player/player.h"
#include "lib/buffers/vbo.h"
#include "lib/buffers/vao.h"
#include "lib/block/block.h"
#include "lib/chunk/chunk.h"

#include "lib/window/window.h"
#include "lib/game/game.h"

#include "lib/objects/cube.h"

#define STB_IMAGE_IMPLEMENTATION
#include "./lib/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



Game game;

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
    game.mouse_callback(xposIn, yposIn);
}

int main() {
    glfwSetInputMode(game.window->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(game.window->glfwWindow, mouse_callback);
    game.loop();
    return 0;
}