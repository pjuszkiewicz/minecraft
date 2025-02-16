#ifndef GAME_H
#define GAME_H

#include "../../engine/renderer/renderer.h"
#include "../../engine/window/window.h"
#include "./game_objects/sphere_object.h"
#include <memory>

class Game {
public:
    Window window;
    Player player;

    std::vector<std::unique_ptr<IGameObject>> gameObjects;
    Renderer renderer = Renderer(gameObjects);

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
