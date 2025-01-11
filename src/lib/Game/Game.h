#ifndef GAME_H
#define GAME_H

#include "../../lib/Renderer/Renderer.h"
#include <unordered_map>
#include "../../lib/Map/PairHash.h"
#include "../../lib/Window/Window.h"


#include <thread>
#include <chrono>

#include "../World/World.h"

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

    int chunkX = 0;
    int lastChunkX = 0;
    int chunkZ = 0;
    int lastChunkZ = 0;

    Game();

    void loop();

    void updateDeltaTime();

    void processInput(GLFWwindow *glfwWindow, float deltaTime);
};

#endif
