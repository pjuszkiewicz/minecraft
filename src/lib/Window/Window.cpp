//
// Created by piotr on 07.01.25.
//

#include "../../lib/Window/Window.h"

int loadGlad() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

Window::Window() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Minecraft", NULL, NULL);
    if (glfwWindow == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(glfwWindow);

    glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_size_callback);

    loadGlad();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    glEnable(GL_CULL_FACE);

    glfwMonitor = glfwGetPrimaryMonitor();
    glfwVideoMode = glfwGetVideoMode(glfwMonitor);
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(glfwWindow);
}

void Window::toggleFullscreen() {
    if (isFullscreen) {
        glfwSetWindowMonitor(glfwWindow, NULL, 100, 100, 1280, 720, 0);
    } else {
        glfwSetWindowMonitor(glfwWindow, glfwMonitor, 0, 0, glfwVideoMode->width, glfwVideoMode->height,
                             glfwVideoMode->refreshRate);
    }
    isFullscreen = !isFullscreen;
}
