#ifndef GAME_H
#define GAME_H

#include "../../lib/Renderer/Renderer.h"

#include <unordered_map>
#include <thread>
#include <chrono>

#include "../World/World.h"
#include "../../lib/Map/PairHash.h"
#include "../../lib/Window/Window.h"
#include "../Constants.h"

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

    Game();

    void prepareChunksLoop();

    void loop();

    void updateDeltaTime();

    void processInput(GLFWwindow *glfwWindow, float deltaTime);

    void destroyBlock();
};

#endif
