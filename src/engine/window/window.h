#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include "../../../vendor/glad/glad.h"
#include <GLFW/glfw3.h>

const int DEFAULT_WINDOW_WIDTH = 1600;
const int DEFAULT_WINDOW_HEIGHT = 900;

class Window {
public:
    int width = DEFAULT_WINDOW_WIDTH;
    int height = DEFAULT_WINDOW_HEIGHT;
    bool isFullscreen = false;
    std::string title = "Minecraft";

    GLFWwindow *glfwWindow;
    GLFWmonitor *glfwMonitor;
    const GLFWvidmode *glfwVideoMode;

    Window();
    bool shouldClose() const;
    void toggleFullscreen();
};

#endif
