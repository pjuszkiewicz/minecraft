#ifndef GAME_H
#define GAME_H

#include "../../lib/Renderer/Renderer.h"
#include <unordered_map>
#include "../../lib/Map/PairHash.h"
#include "../../lib/Window/Window.h"


class Game {
public:
    Window *window;
    Renderer *renderer;
    Player player;

    std::unordered_map<std::pair<int, int>, Chunk, PairHash> chunks;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    float lastX = SCR_WIDTH / 2.0f;
    float lastY = SCR_HEIGHT / 2.0f;

    bool firstMouse = true;

    int fps = 0;
    float lastFpsTime = 0.0f;


    Game();

    ~Game();

    void loop();

    void updateDeltaTime();

    void updateFpsTime();

    void updateChunk(int x, int z);

    bool isBlockAt(glm::vec3 pos);

    void generateChunks();

    void processInput(GLFWwindow *glfwWindow, float deltaTime);

    void mouse_callback(double xposIn, double yposIn);
};

#endif
