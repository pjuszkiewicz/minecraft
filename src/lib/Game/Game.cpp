#include "../../lib/Game/Game.h"
#include <future>
#include <functional>

#include "../Renderer/ChunkBuilder.h"

void Game::prepareChunksLoop() {
    int chunkX = 0;
    int lastChunkX = 0;
    int newChunkX = 0;

    int chunkZ = 0;
    int lastChunkZ = 0;
    int newChunkZ = 0;

    while (true) {
        newChunkX = (player.Position.x - (static_cast<int>(player.Position.x) % CHUNK_WIDTH)) / CHUNK_WIDTH;
        newChunkZ = (player.Position.z - (static_cast<int>(player.Position.z) % CHUNK_WIDTH)) / CHUNK_WIDTH;

        if (newChunkX != chunkX || newChunkZ != chunkZ) {
            lastChunkX = chunkX;
            chunkX = newChunkX;
            lastChunkZ = chunkZ;
            chunkZ = newChunkZ;
        }

        if (renderer.chunksToAdd.size() == 0) {
            renderer.isReadyToAdd = false;
            for (int i = -RENDER_DISTANCE; i <= RENDER_DISTANCE; i++) {
                for (int j = -RENDER_DISTANCE; j <= RENDER_DISTANCE; j++) {
                    int x = chunkX + i;
                    int z = chunkZ + j;

                    auto key = std::make_pair(x, z);

                    auto foundChunkMesh = renderer.chunkMeshes.find(key);
                    if (foundChunkMesh != renderer.chunkMeshes.end()) {
                        continue;
                    }

                    auto foundChunk = world.chunks.find(key);
                    if (foundChunk != world.chunks.end()) {
                        Chunk *forwardChunk = nullptr;
                        auto forward = world.chunks.find(std::make_pair(x, z + 1));
                        if (forward != world.chunks.end()) forwardChunk = &forward->second;

                        Chunk *backChunk = nullptr;
                        auto back = world.chunks.find(std::make_pair(x, z - 1));
                        if (back != world.chunks.end()) backChunk = &back->second;

                        Chunk *leftChunk = nullptr;
                        auto left = world.chunks.find(std::make_pair(x - 1, z));
                        if (left != world.chunks.end()) leftChunk = &left->second;

                        Chunk *rightChunk = nullptr;
                        auto right = world.chunks.find(std::make_pair(x + 1, z));
                        if (right != world.chunks.end()) rightChunk = &right->second;

                        ChunkBuilder builder(
                            foundChunk->second,
                            forwardChunk,
                            backChunk,
                            leftChunk,
                            rightChunk
                        );

                        renderer.chunksToAdd.push_back(builder);
                    }
                }
            }
            renderer.isReadyToAdd = true;
        }


        for (auto chunkMeshPair: renderer.chunkMeshes) {
            ChunkMesh chunkMesh = chunkMeshPair.second;

            if (abs(chunkMesh.chunkX - chunkX) > RENDER_DISTANCE || abs(chunkMesh.chunkZ - chunkZ) > RENDER_DISTANCE) {
                auto pair = std::make_pair(chunkMesh.chunkX, chunkMesh.chunkZ);
                renderer.chunksToRemove.push_back(pair);
            }
        }


        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

Game::Game() {
    world.generateChunks();
    std::thread t(&Game::prepareChunksLoop, this);
    t.detach();
}


void Game::loop() {
    while (!window.shouldClose()) {
        updateDeltaTime();

        player.update(deltaTime);
        renderer.Draw(player, world.chunks);

        glfwSwapBuffers(window.glfwWindow);
        glfwPollEvents();

        processInput(window.glfwWindow, deltaTime);
    }

    glfwTerminate();
}

void Game::updateDeltaTime() {
    float currentTime = glfwGetTime();

    deltaTime = currentTime - lastFrame;
    lastFrame = currentTime;

    fps++;
    if (currentTime - lastFpsTime > 1.0f) {
        // std::cout << "FPS: " << fps << std::endl;
        fps = 0;
        lastFpsTime = currentTime;
    }
}

void Game::destroyBlock() {
    glm::vec3 pos = player.camera.Position;
    glm::vec3 camDir = player.camera.getCameraDirection();

    int chunkX = static_cast<int>(floor(pos.x / CHUNK_WIDTH));
    int chunkZ = static_cast<int>(floor(pos.z / CHUNK_WIDTH));
    // std::cout << chunkX << ", " << chunkZ << std::endl;

    for (float i = 0; i < MAX_BREAK_DISTANCE; i += 0.01f) {
        glm::vec3 offset = camDir * i;
        glm::vec3 blockPos = pos + offset;

        if (world.isBlockAt(blockPos)) {
            world.removeBlockAt(blockPos);
            break;
        }
    }

    rerenderChunks(chunkX, chunkZ);
}

void Game::createBlock() {
    glm::vec3 pos = player.camera.Position;
    glm::vec3 camDir = player.camera.getCameraDirection();

    int chunkX = static_cast<int>(floor(pos.x / CHUNK_WIDTH));
    int chunkZ = static_cast<int>(floor(pos.z / CHUNK_WIDTH));
    // std::cout << chunkX << ", " << chunkZ << std::endl;

    glm::vec3 posToPlace(0, 0, 0);
    bool check1 = false;
    bool hittedBlock = false;

    for (float i = 0; i < MAX_BREAK_DISTANCE; i += 0.01f) {
        glm::vec3 offset = camDir * i;
        glm::vec3 blockPos = pos + offset;

        if (!world.isBlockAt(blockPos)) {
            posToPlace = pos + offset;
            check1 = true;
        } else {
            hittedBlock = true;
            break;
        }
    }

    if (check1 && hittedBlock) {
        world.placeBlockAt(posToPlace);

        rerenderChunks(chunkX, chunkZ);
    }
}

void Game::rerenderChunks(int chunkX, int chunkZ) {
    for (int x = chunkX - 1; x <= chunkX + 1; x++) {
        for (int z = chunkZ - 1; z <= chunkZ + 1; z++) {
            auto key = std::make_pair(x, z);
            auto foundChunk = world.chunks.find(key);
            if (foundChunk != world.chunks.end()) {
                Chunk *forwardChunk = nullptr;
                auto forward = world.chunks.find(std::make_pair(x, z + 1));
                if (forward != world.chunks.end()) forwardChunk = &forward->second;

                Chunk *backChunk = nullptr;
                auto back = world.chunks.find(std::make_pair(x, z - 1));
                if (back != world.chunks.end()) backChunk = &back->second;

                Chunk *leftChunk = nullptr;
                auto left = world.chunks.find(std::make_pair(x - 1, z));
                if (left != world.chunks.end()) leftChunk = &left->second;

                Chunk *rightChunk = nullptr;
                auto right = world.chunks.find(std::make_pair(x + 1, z));
                if (right != world.chunks.end()) rightChunk = &right->second;

                ChunkBuilder builder(
                    foundChunk->second,
                    forwardChunk,
                    backChunk,
                    leftChunk,
                    rightChunk
                );

                auto found = renderer.chunkMeshes.find(key);
                if (found != renderer.chunkMeshes.end()) {
                    auto &mesh = found->second;
                    mesh.positions = builder.positions;
                    mesh.textures = builder.textures;
                    mesh.ambientOcclusions = builder.ambientOcclusions;
                    mesh.updateBuffers();
                }
            }
        }
    }
}


void Game::processInput(GLFWwindow *glfwWindow, float deltaTime) {
    if (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(glfwWindow, true);
    //
    if (glfwGetKey(glfwWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        player.HandlePlayerMove(SPRINT, deltaTime);
    if (glfwGetKey(glfwWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
        player.HandlePlayerMove(WALK, deltaTime);

    if (glfwGetKey(glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
        player.HandlePlayerMove(FORWARD, deltaTime);
    if (glfwGetKey(glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
        player.HandlePlayerMove(BACKWARD, deltaTime);
    if (glfwGetKey(glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
        player.HandlePlayerMove(LEFT, deltaTime);
    if (glfwGetKey(glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
        player.HandlePlayerMove(RIGHT, deltaTime);

    if (glfwGetKey(glfwWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
        player.HandlePlayerMove(UP, deltaTime);
    if (glfwGetKey(glfwWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        player.HandlePlayerMove(DOWN, deltaTime);

    if (glfwGetKey(glfwWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
        player.HandlePlayerMove(JUMP, deltaTime);

    if (glfwGetKey(glfwWindow, GLFW_KEY_F11) == GLFW_PRESS)
        window.toggleFullscreen();

    if (glfwGetKey(glfwWindow, GLFW_KEY_O) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(glfwWindow, GLFW_KEY_P) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    if (glfwGetKey(glfwWindow, GLFW_KEY_K) == GLFW_PRESS) {
        std::cout << "LET ME GO" << std::endl;
        glfwSetInputMode(window.glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }


    if (glfwGetKey(glfwWindow, GLFW_KEY_L) == GLFW_PRESS) {
        std::cout << "LET ME GO" << std::endl;
        glfwSetInputMode(window.glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }


    if (glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        isLeftMousePressed = false;
    }

    if (glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if (!isLeftMousePressed) {
            destroyBlock();
        }
        isLeftMousePressed = false;
    }

    if (glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
        isRightMousePressed = false;
    }

    if (glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        if (!isRightMousePressed) {
            createBlock();
        }
        isRightMousePressed = false;
    }
}
