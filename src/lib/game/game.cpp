#include "../../lib/Game/Game.h"
#define STB_PERLIN_IMPLEMENTATION
#include "../stb_perlin.h"

Game::Game() {
    window = new Window();
    renderer = new Renderer(player);

    generateChunks();
}

Game::~Game() {
    delete window;
    delete renderer;
}

void Game::loop() {
    while (!window->shouldClose()) {
        updateDeltaTime();
        updateFpsTime();
        player.update(deltaTime);
        renderer->draw(
            player,
            chunks);

        glfwSwapBuffers(window->glfwWindow);
        glfwPollEvents();

        processInput(window->glfwWindow, deltaTime);
    }

    glfwTerminate();
}

void Game::updateDeltaTime() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void Game::updateFpsTime() {
    double currentTime = glfwGetTime();
    fps++;
    if (currentTime - lastFpsTime > 1.0f) {
        // std::cout << "FPS: " << fps << std::endl;
        fps = 0;
        lastFpsTime = currentTime;
    }
}

void Game::updateChunk(int x, int z) {
    const glm::vec3 top = glm::vec3(0, 1, 0);
    const glm::vec3 bottom = glm::vec3(0, -1, 0);
    const glm::vec3 left = glm::vec3(-1, 0, 0);
    const glm::vec3 right = glm::vec3(1, 0, 0);
    const glm::vec3 forward = glm::vec3(0, 0, 1);
    const glm::vec3 back = glm::vec3(0, 0, -1);

    auto chunkIndex = chunks.find(std::make_pair(x, z));

    if (chunkIndex != chunks.end()) {
        Chunk chunk = chunkIndex->second;

        for (int x = 0; x < CHUNK_WIDTH; x++) {
            for (int y = 0; y < CHUNK_HEIGHT; y++) {
                for (int z = 0; z < CHUNK_WIDTH; z++) {
                    Block block = chunk.getBlock(glm::vec3(x, y, z));
                    if (!isBlockAt(glm::vec3(x, y, z) + top)) block.drawTop = true;
                    if (!isBlockAt(glm::vec3(x, y, z) + bottom)) block.drawBottom = true;
                    if (!isBlockAt(glm::vec3(x, y, z) + left)) block.drawLeft = true;
                    if (!isBlockAt(glm::vec3(x, y, z) + right)) block.drawRight = true;
                    if (!isBlockAt(glm::vec3(x, y, z) + forward)) block.drawFront = true;
                    if (!isBlockAt(glm::vec3(x, y, z) + back)) block.drawBack = true;
                }
            }
        }
    }
}

bool Game::isBlockAt(glm::vec3 pos) {
    int chunkWorldX = pos.x - ((int) pos.x % CHUNK_WIDTH);
    int chunkWorldZ = pos.z - ((int) pos.z % CHUNK_WIDTH);
    int chunkX = chunkWorldX / CHUNK_WIDTH;
    int chunkZ = chunkWorldZ / CHUNK_WIDTH;

    auto chunkIndex = chunks.find(std::make_pair(chunkX, chunkZ));
    if (chunkIndex != chunks.end()) {
        Chunk chunk = chunkIndex->second;
        Block block = chunk.getBlock(pos);

        return block.type != BlockType::AIR;
    }

    return false;
}

float perlinNoise(float x, float z, int octaves, float persistence, float scale) {
    float noise = 0.0f;
    float amplitude = 1.0f;
    float frequency = 1.0f;
    float maxValue = 0.0f; // Do normalizacji

    for (int i = 0; i < octaves; i++) {
        noise += amplitude * stb_perlin_noise3(x * frequency * scale, 0.0f, z * frequency * scale, 0, 0, 0);
        maxValue += amplitude;

        amplitude *= persistence; // Zmniejsz amplitudę
        frequency *= 2.0f;        // Zwiększ częstotliwość
    }

    return noise / maxValue; // Normalizuj wynik do zakresu 0-1
}

void Game::generateChunks() {

    for (int x = -20; x <= 20; x++) {
        for (int z = -20; z <= 20; z++) {
            Chunk chunk(x, z);

            int chunkX = x * CHUNK_WIDTH;
            int chunkZ = z * CHUNK_WIDTH;

            // Generowanie chunka
            for (int bx = 0; bx < CHUNK_WIDTH; bx++) {
                for (int bz = 0; bz < CHUNK_WIDTH; bz++) {

                    float scale = 0.1;

                    // float noise = stb_perlin_noise3((chunkX + bx) * scale, 0.0f, (chunkZ + bz) * scale, 0, 0, 0);
                    float noise = perlinNoise((chunkX + bx), (chunkZ + bz), 3, 0, scale) + 0.5;
                    if (noise < 0.0f) noise = 0.0;

                    int height = (int) (noise * 32);


                    for (int by = 0; by < height + 1; by++) {
                        int xOffset = x * CHUNK_WIDTH;
                        int zOffset = z * CHUNK_WIDTH;

                        glm::vec3 pos(bx + xOffset, by, bz + zOffset);
                        Block block(DIAMOND, pos);

                        chunk.blocks[bx][by][bz] = block;
                    }
                }
            }

            chunks[{x, z}] = chunk;
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
        player.HandlePlayerMove(JUMP, deltaTime);

    if (glfwGetKey(glfwWindow, GLFW_KEY_F11) == GLFW_PRESS)
        window->toggleFullscreen();

    if (glfwGetKey(glfwWindow, GLFW_KEY_O) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(glfwWindow, GLFW_KEY_P) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Game::mouse_callback(double xposIn, double yposIn) {
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

    player.HandleMouseMove(xoffset, yoffset);
}
