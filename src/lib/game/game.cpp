//
// Created by piotr on 07.01.25.
//

#include "../../lib/game/game.h"

Game::Game() {
    window = new Window();
    renderer = new Renderer();

    player = new Player(glm::vec3(0.0f, 17.0f, 0.0f));

    generateChunks();
}

Game::~Game() {
    delete window;
    delete renderer;
}

void Game::loop() {
    while (!window->shouldClose()) {
        updateDeltaTime();
        updateFpsTime();
        player->update(deltaTime);
        renderer->draw(player, chunks);


        // opengl stuff
        glfwSwapBuffers(window->glfwWindow);
        glfwPollEvents();

        processInput(window->glfwWindow, deltaTime);
    }

    glfwTerminate();
}

void Game::updateDeltaTime() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void Game::updateFpsTime() {
    double currentTime = glfwGetTime();
    fps++;
    if (currentTime - lastFpsTime > 1.0f) {
        std::cout << "FPS: " << fps << std::endl;
        fps = 0;
        lastFpsTime = currentTime;
    }
}

void Game::updateChunk(int x, int z) {
    const glm::vec3 top = glm::vec3(0, 1, 0);
    const glm::vec3 bottom = glm::vec3(0, -1, 0);
    const glm::vec3 left = glm::vec3(-1, 0, 0);
    const glm::vec3 right = glm::vec3(1, 0, 0);
    const glm::vec3 forward = glm::vec3(0, 0, 1);
    const glm::vec3 back = glm::vec3(0, 0, -1);

    auto chunkIndex = chunks.find(std::make_pair(x, z));

    if (chunkIndex != chunks.end()) {
        Chunk chunk = chunkIndex->second;

        for (int x = 0; x < CHUNK_WIDTH; x++) {
            for (int y = 0; y < CHUNK_HEIGHT; y++) {
                for (int z = 0; z < CHUNK_WIDTH; z++) {
                    Block block = chunk.getBlock(glm::vec3(x, y, z));
                    if (!isBlockAt(glm::vec3(x, y, z) + top)) block.drawTop = true;
                    if (!isBlockAt(glm::vec3(x, y, z) + bottom)) block.drawBottom = true;
                    if (!isBlockAt(glm::vec3(x, y, z) + left)) block.drawLeft = true;
                    if (!isBlockAt(glm::vec3(x, y, z) + right)) block.drawRight = true;
                    if (!isBlockAt(glm::vec3(x, y, z) + forward)) block.drawFront = true;
                    if (!isBlockAt(glm::vec3(x, y, z) + back)) block.drawBack = true;
                }
            }
        }
    }
}

bool Game::isBlockAt(glm::vec3 pos) {
    int chunkWorldX = pos.x - ((int) pos.x % CHUNK_WIDTH);
    int chunkWorldZ = pos.z - ((int) pos.z % CHUNK_WIDTH);
    int chunkX = chunkWorldX / CHUNK_WIDTH;
    int chunkZ = chunkWorldZ / CHUNK_WIDTH;

    auto chunkIndex = chunks.find(std::make_pair(chunkX, chunkZ));
    if (chunkIndex != chunks.end()) {
        Chunk chunk = chunkIndex->second;
        Block block = chunk.getBlock(pos);

        return block.type != BlockType::AIR;
    }

    return false;
}

void Game::generateChunks() {
    for (int x = -1; x <= 1; x++) {
        for (int z = -1; z <= 1; z++) {
            Chunk chunk(x, z);

            // Generowanie chunka
            for (int bx = 0; bx < CHUNK_WIDTH; bx++) {
                for (int by = 0; by < CHUNK_HEIGHT; by++) {
                    for (int bz = 0; bz < CHUNK_WIDTH; bz++) {
                        int xOffset = x * CHUNK_WIDTH;
                        int zOffset = z * CHUNK_WIDTH;

                        glm::vec3 pos(bx + xOffset, by, bz + zOffset);
                        Block block(DIAMOND, pos);

                        chunk.blocks[bx][by][bz] = block;
                    }
                }
            }

            chunks[{x, z}] = chunk;

            // updateChunk(x, z);
        }
    }
}

void Game::processInput(GLFWwindow *glfwWindow, float deltaTime) {
    if (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(glfwWindow, true);
    //
    if (glfwGetKey(glfwWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        player->HandlePlayerMove(SPRINT, deltaTime);
    if (glfwGetKey(glfwWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
        player->HandlePlayerMove(WALK, deltaTime);

    if (glfwGetKey(glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
        player->HandlePlayerMove(FORWARD, deltaTime);
    if (glfwGetKey(glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
        player->HandlePlayerMove(BACKWARD, deltaTime);
    if (glfwGetKey(glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
        player->HandlePlayerMove(LEFT, deltaTime);
    if (glfwGetKey(glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
        player->HandlePlayerMove(RIGHT, deltaTime);

    if (glfwGetKey(glfwWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
        player->HandlePlayerMove(JUMP, deltaTime);

    if (glfwGetKey(glfwWindow, GLFW_KEY_F11) == GLFW_PRESS)
        window->toggleFullscreen();

    if (glfwGetKey(glfwWindow, GLFW_KEY_O) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(glfwWindow, GLFW_KEY_P) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Game::mouse_callback(double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    player->HandleMouseMove(xoffset, yoffset);
}
