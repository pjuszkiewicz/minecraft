#ifndef GAME_H
#define GAME_H

#include "../../lib/Renderer/Renderer.h"
#include <unordered_map>
#include "../../lib/Map/PairHash.h"
#include "../../lib/Window/Window.h"


#include <thread>
#include <chrono>

class Game {
public:
    Window *window;
    Renderer *renderer;
    Player player;

    std::unordered_map<std::pair<int, int>, Chunk, PairHash> chunks;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    int fps = 0;
    float lastFpsTime = 0.0f;
    int chunkX = 0;
    int lastChunkX = 0;
    int chunkZ = 0;
    int lastChunkZ = 0;

    Game();

    ~Game();

    void loop();

    void updateDeltaTime();

    void updateFpsTime();

    void updateChunk(int x, int z);

    bool isBlockAt(glm::vec3 pos);

    void generateChunks();

    void processInput(GLFWwindow *glfwWindow, float deltaTime);

    void chunkUpdateLoop();
};

#endif
