#ifndef WINDOW_H
#define WINDOW_H

#include "../../../vendor/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

const int SCR_WIDTH = 1600;
const int SCR_HEIGHT = 900;

class Window {
public:
    GLFWwindow *glfwWindow;
    GLFWmonitor *glfwMonitor;
    const GLFWvidmode *glfwVideoMode;

    bool isFullscreen = false;

    Window();
    bool shouldClose() const;
    void toggleFullscreen();
};

#endif
