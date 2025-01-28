#ifndef GAME_H
#define GAME_H

#include "../../lib/Renderer/Renderer.h"

#include "../World/World.h"
#include "../../lib/Window/Window.h"

class Game {
public:
    Window window;
    Renderer renderer;
    Player player;
    World world;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float lastFpsTime = 0.0f;
    int fps = 0;

    bool isLeftMousePressed = false;
    bool isRightMousePressed = false;

    Game();

    void prepareChunksLoop();

    void loop();

    void updateDeltaTime();

    void processInput(GLFWwindow *glfwWindow, float deltaTime);

    void destroyBlock();
    void createBlock();
    void rerenderChunks(int chunkX, int chunkZ);
};

#endif
