#ifndef GAME_H
#define GAME_H

#include "../../lib/renderer/renderer.h"

const int RENDER_CHUNKS = 2;

class Game {
public:
    Window *window;
    Renderer *renderer;
    Player *player;
    Chunk chunks[RENDER_CHUNKS][RENDER_CHUNKS];

    Game() {
        window = new Window();
        renderer = new Renderer();

        player = new Player(glm::vec3(0.0f, 0.0f, 0.0f));

        generateChunks();

        loop();
    }

    ~Game() {
        delete window;
        delete renderer;
    }

    void loop() {
        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

        while (!window->shouldClose()) {
            // timing
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            //player
            player->Update(deltaTime);

            // drawing
            renderer->draw();


            // opengl stuff
            glfwSwapBuffers(window->glfwWindow);
            glfwPollEvents();
        }

        glfwTerminate();
    }

    void generateChunks() {
        for (int i = 0; i < RENDER_CHUNKS; i++) {
            for (int j = 0; j < RENDER_CHUNKS; j++) {
                Chunk chunk(i * CHUNK_WIDTH, j * CHUNK_WIDTH);

                for (int x = 0; x < CHUNK_WIDTH; x++) {
                    // for (int y = 0; y < CHUNK_HEIGHT; y++)
                    for (int y = 0; y < 1; y++) {
                        // for (int z = 0; z < CHUNK_WIDTH; z++)
                        for (int z = 0; z < 1; z++) {
                            int xOffset = i * CHUNK_WIDTH;
                            int zOffset = j * CHUNK_WIDTH;

                            glm::vec3 pos(x + xOffset, y, z + zOffset);
                            Block block(DIRT, pos);
                            chunk.blocks[x][y][z] = block;
                        }
                    }
                }

                chunks[i][j] = chunk;
            }
        }
    }
};

#endif
