#include "../../engine/game/game.h"
#include <future>

#include "game_objects/plane_object.h"

Game::Game() {
    for (int x = 0; x < 1; x++) {
        for (int z = 0; z < 1; z++) {
            auto object = std::make_unique<SphereObject>();
            object->position = glm::vec3(x * 1.0f, 0, z * 1.0f);
            gameObjects.push_back(std::move(object));
        }
    }
}

void Game::loop() {
    while (!window.shouldClose()) {
        updateDeltaTime();

        player.update(deltaTime);
        renderer.draw(player);

        glfwSwapBuffers(window.glfwWindow);
        glfwPollEvents();

        processInput();
    }

    glfwTerminate();
}

void Game::updateDeltaTime() {
    auto currentTime = static_cast<float>(glfwGetTime());

    deltaTime = currentTime - lastFrame;
    lastFrame = currentTime;

    fps++;
    if (currentTime - lastFpsTime > 1.0f) {
        // std::cout << "FPS: " << fps << std::endl;
        fps = 0;
        lastFpsTime = currentTime;
    }
}


void Game::processInput() {
    // Klawiatura
    if (glfwGetKey(window.glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window.glfwWindow, true);

    if (glfwGetKey(window.glfwWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        player.handlePlayerMove(SPRINT, deltaTime);

    if (glfwGetKey(window.glfwWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
        player.handlePlayerMove(WALK, deltaTime);

    if (glfwGetKey(window.glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
        player.handlePlayerMove(FORWARD, deltaTime);

    if (glfwGetKey(window.glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
        player.handlePlayerMove(BACKWARD, deltaTime);

    if (glfwGetKey(window.glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
        player.handlePlayerMove(LEFT, deltaTime);

    if (glfwGetKey(window.glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
        player.handlePlayerMove(RIGHT, deltaTime);

    if (glfwGetKey(window.glfwWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
        player.handlePlayerMove(UP, deltaTime);

    if (glfwGetKey(window.glfwWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        player.handlePlayerMove(DOWN, deltaTime);

    if (glfwGetKey(window.glfwWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
        player.handlePlayerMove(JUMP, deltaTime);

    if (glfwGetKey(window.glfwWindow, GLFW_KEY_F11) == GLFW_PRESS)
        window.toggleFullscreen();

    if (glfwGetKey(window.glfwWindow, GLFW_KEY_O) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (glfwGetKey(window.glfwWindow, GLFW_KEY_P) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (glfwGetKey(window.glfwWindow, GLFW_KEY_K) == GLFW_PRESS) {
        glfwSetInputMode(window.glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if (glfwGetKey(window.glfwWindow, GLFW_KEY_L) == GLFW_PRESS) {
        glfwSetInputMode(window.glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}
