#ifndef WINDOW_H
#define WINDOW_H

#include "../../lib/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

const int SCR_WIDTH = 1280;
const int SCR_HEIGHT = 720;

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
