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

    Window() {
        createWindow();
    }

    GLFWwindow *createWindow() {
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
        // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        //    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        //    glfwSetCursorPosCallback(window, mouse_callback);

        loadGlad();

        glEnable(GL_DEPTH_TEST);

        return glfwWindow;
    }

    bool shouldClose() const {
        // if (!window) return false;
        return glfwWindowShouldClose(glfwWindow);
    }


    int loadGlad() {
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        return 0;
    }


    void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
        //    float xpos = static_cast<float>(xposIn);
        //    float ypos = static_cast<float>(yposIn);
        //
        //    if (firstMouse)
        //    {
        //        lastX = xpos;
        //        lastY = ypos;
        //        firstMouse = false;
        //    }
        //
        //    float xoffset = xpos - lastX;
        //    float yoffset = lastY - ypos;
        //
        //    lastX = xpos;
        //    lastY = ypos;
        //
        //    player.HandleMouseMove(xoffset, yoffset);
    }

    void processInput(GLFWwindow *window) {
        //    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        //        glfwSetWindowShouldClose(window, true);
        //
        //    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        //        player.HandlePlayerMove(SPRINT, deltaTime);
        //    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
        //        player.HandlePlayerMove(WALK, deltaTime);
        //
        //    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        //        player.HandlePlayerMove(FORWARD, deltaTime);
        //    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        //        player.HandlePlayerMove(BACKWARD, deltaTime);
        //    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        //        player.HandlePlayerMove(LEFT, deltaTime);
        //    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        //        player.HandlePlayerMove(RIGHT, deltaTime);
        //
        //    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        //        player.HandlePlayerMove(JUMP, deltaTime);
        //
        //    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        //        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        //        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }


    void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    }
};

#endif
