//
// Created by piotr on 07.01.25.
//

#include "window.h"

int loadGlad() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    return 0;
}

Window::Window() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (glfwWindow == NULL) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(glfwWindow);

    // Przypisanie this dla callbacku z resize
    glfwSetWindowUserPointer(glfwWindow, this);

    // Callback resize
    glfwSetFramebufferSizeCallback(glfwWindow, [](GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);

        auto *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
        win->width = width;
        win->height = height;
    });

    loadGlad();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    glEnable(GL_CULL_FACE);

    // Korekcja gammy
    // glEnable(GL_FRAMEBUFFER_SRGB);

    glfwMonitor = glfwGetPrimaryMonitor();
    glfwVideoMode = glfwGetVideoMode(glfwMonitor);
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(glfwWindow);
}

void Window::toggleFullscreen() {
    if (isFullscreen) {
        glfwSetWindowMonitor(glfwWindow, NULL, 100, 100, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, 0);
    } else {
        glfwSetWindowMonitor(
            glfwWindow,
            glfwMonitor,
            0,
            0,
            glfwVideoMode->width,
            glfwVideoMode->height,
            glfwVideoMode->refreshRate
        );
    }

    isFullscreen = !isFullscreen;
}