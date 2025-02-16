#ifndef GAME_H
#define GAME_H

#include "../../engine/renderer/renderer.h"
#include "../../engine/window/window.h"

class Game {
public:
    Window window;
    Renderer renderer;
    Player player;

    int fps = 0;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float lastFpsTime = 0.0f;

    Game();

    void loop();

    void updateDeltaTime();

    void processInput();
};

#endif
