#include "../../lib/Game/Game.h"
#include <future>
#include <functional>

void Game::test() {
    while (true) {
        for (int i = -RENDER_DISTANCE; i <= RENDER_DISTANCE; i++) {
            for (int j = -RENDER_DISTANCE; j <= RENDER_DISTANCE; j++) {
                int x = chunkX + i;
                int z = chunkZ + j;

                // auto pair = std::make_pair(x, z);

                auto key = std::make_pair(x, z);

                auto foundChunkMesh = renderer.chunkMeshes.find(key);
                if (foundChunkMesh != renderer.chunkMeshes.end()) {
                    continue;
                }

                auto foundChunk = world.chunks.find(key);
                if (foundChunk != world.chunks.end()) {
                    renderer.chunksToRender.push_back(foundChunk->second);
                }
            }
        }


        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

Game::Game() {
    world.generateChunks();
    std::thread t(&Game::test, this);
    t.detach();
}


void Game::loop() {
    while (!window.shouldClose()) {
        updateDeltaTime();

        player.update(deltaTime);

        renderer.draw(player, world.chunks);

        int newChunkX = (player.Position.x - (static_cast<int>(player.Position.x) % CHUNK_WIDTH)) / CHUNK_WIDTH;
        int newChunkZ = (player.Position.z - (static_cast<int>(player.Position.z) % CHUNK_WIDTH)) / CHUNK_WIDTH;

        if (newChunkX != chunkX || newChunkZ != chunkZ) {
            lastChunkX = chunkX;
            chunkX = newChunkX;
            lastChunkZ = chunkZ;
            chunkZ = newChunkZ;
        }


        glfwSwapBuffers(window.glfwWindow);
        glfwPollEvents();

        processInput(window.glfwWindow, deltaTime);
    }

    glfwTerminate();
}

void Game::updateDeltaTime() {
    float currentTime = glfwGetTime();

    deltaTime = currentTime - lastFrame;
    lastFrame = currentTime;

    fps++;
    if (currentTime - lastFpsTime > 1.0f) {
        // std::cout << "FPS: " << fps << std::endl;
        std::cout << renderer.count << std::endl;
        fps = 0;
        lastFpsTime = currentTime;
    }
}

void Game::processInput(GLFWwindow *glfwWindow, float deltaTime) {
    if (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(glfwWindow, true);
    //
    if (glfwGetKey(glfwWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        player.HandlePlayerMove(SPRINT, deltaTime);
    if (glfwGetKey(glfwWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
        player.HandlePlayerMove(WALK, deltaTime);

    if (glfwGetKey(glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
        player.HandlePlayerMove(FORWARD, deltaTime);
    if (glfwGetKey(glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
        player.HandlePlayerMove(BACKWARD, deltaTime);
    if (glfwGetKey(glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
        player.HandlePlayerMove(LEFT, deltaTime);
    if (glfwGetKey(glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
        player.HandlePlayerMove(RIGHT, deltaTime);

    if (glfwGetKey(glfwWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
        player.HandlePlayerMove(JUMP, deltaTime);

    if (glfwGetKey(glfwWindow, GLFW_KEY_F11) == GLFW_PRESS)
        window.toggleFullscreen();

    if (glfwGetKey(glfwWindow, GLFW_KEY_O) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(glfwWindow, GLFW_KEY_P) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
