#include "../../lib/Game/Game.h"
#include <future>
#include <functional>

void Game::prepareChunksLoop() {
    int chunkX = 0;
    int lastChunkX = 0;
    int newChunkX = 0;

    int chunkZ = 0;
    int lastChunkZ = 0;
    int newChunkZ = 0;

    while (true) {
        newChunkX = (player.Position.x - (static_cast<int>(player.Position.x) % CHUNK_WIDTH)) / CHUNK_WIDTH;
        newChunkZ = (player.Position.z - (static_cast<int>(player.Position.z) % CHUNK_WIDTH)) / CHUNK_WIDTH;

        if (newChunkX != chunkX || newChunkZ != chunkZ) {
            lastChunkX = chunkX;
            chunkX = newChunkX;
            lastChunkZ = chunkZ;
            chunkZ = newChunkZ;
        }

        if (renderer.chunksToAdd.size() == 0) {
            renderer.isReadyToAdd = false;
            for (int i = -RENDER_DISTANCE; i <= RENDER_DISTANCE; i++) {
                for (int j = -RENDER_DISTANCE; j <= RENDER_DISTANCE; j++) {
                    int x = chunkX + i;
                    int z = chunkZ + j;

                    auto key = std::make_pair(x, z);

                    auto foundChunkMesh = renderer.chunkMeshes.find(key);
                    if (foundChunkMesh != renderer.chunkMeshes.end()) {
                        continue;
                    }

                    auto foundChunk = world.chunks.find(key);
                    if (foundChunk != world.chunks.end()) {
                        renderer.chunksToAdd.push_back(foundChunk->second);
                    }
                }
            }
            renderer.isReadyToAdd = true;
        }


        for (auto chunkMeshPair: renderer.chunkMeshes) {
            ChunkMesh chunkMesh = chunkMeshPair.second;

            if (abs(chunkMesh.chunkX - chunkX) > RENDER_DISTANCE || abs(chunkMesh.chunkZ - chunkZ) > RENDER_DISTANCE) {
                auto pair = std::make_pair(chunkMesh.chunkX, chunkMesh.chunkZ);
                renderer.chunksToRemove.push_back(pair);
                // renderer.chunkMeshes.erase(pair);
            }
        }


        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

Game::Game() {
    world.generateChunks();
    std::thread t(&Game::prepareChunksLoop, this);
    t.detach();
}


void Game::loop() {
    while (!window.shouldClose()) {
        updateDeltaTime();

        player.update(deltaTime);
        renderer.draw(player, world.chunks);

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
        std::cout << "FPS: " << fps << std::endl;
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
