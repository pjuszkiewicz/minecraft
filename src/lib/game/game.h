#ifndef GAME_H
#define GAME_H

#include "../../lib/renderer/renderer.h"
#include <unordered_map>
#include "../../lib/map/pair_hash.h"


class Game {
public:
    Window *window;
    Renderer *renderer;
    Player *player;
    Chunk chunks[RENDER_CHUNKS][RENDER_CHUNKS];

    std::unordered_map<std::pair<int, int>, Chunk, PairHash> newChunks;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    float lastX = SCR_WIDTH / 2.0f;
    float lastY = SCR_HEIGHT / 2.0f;

    bool firstMouse = true;

    Game() {
        window = new Window();
        renderer = new Renderer();

        player = new Player(glm::vec3(0.0f, 0.0f, 0.0f));

        generateChunks();
    }

    ~Game() {
        delete window;
        delete renderer;
    }

    void loop() {
        while (!window->shouldClose()) {
            updateDeltaTime();
            player->update(deltaTime);
            renderer->draw(player, newChunks);


            // opengl stuff
            glfwSwapBuffers(window->glfwWindow);
            glfwPollEvents();

            processInput(window->glfwWindow, deltaTime);
        }

        glfwTerminate();
    }

    void updateDeltaTime() {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }

    void generateChunks() {
        for (int x = 0; x <= 2; x++) {
            for (int z = 0; z <= 2; z++) {
                Chunk chunk(x, z);

                // Generowanie chunka
                for (int bx = 0; bx < CHUNK_WIDTH; bx++) {
                    for (int by = 0; by < CHUNK_HEIGHT; by++) {
                        for (int bz = 0; bz < CHUNK_WIDTH; bz++) {

                            // if (by == CHUNK_HEIGHT - 1) {
                            //     if (bx == 0 || bz == CHUNK_WIDTH - 1) {
                            //         continue;
                            //     }
                            // }

                            int xOffset = x * CHUNK_WIDTH;
                            int zOffset = z * CHUNK_WIDTH;

                            glm::vec3 pos(bx + xOffset, by, bz + zOffset);
                            Block block(DIAMOND, pos);
                            chunk.blocks[bx][by][bz] = block;
                        }
                    }
                }

                newChunks[{x, z}] = chunk;
            }
        }
    }

    void processInput(GLFWwindow *window, float deltaTime) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        //
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            player->HandlePlayerMove(SPRINT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
            player->HandlePlayerMove(WALK, deltaTime);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            player->HandlePlayerMove(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            player->HandlePlayerMove(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            player->HandlePlayerMove(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            player->HandlePlayerMove(RIGHT, deltaTime);

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            player->HandlePlayerMove(JUMP, deltaTime);

        if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    void mouse_callback(double xposIn, double yposIn) {
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
};

#endif
