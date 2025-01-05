#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>

#include "lib/shader/shader.h"
#include "lib/texture/texture.h"
#include "lib/camera/camera.h"
#include "lib/player/player.h"
#include "lib/buffers/vbo.h"
#include "lib/buffers/vao.h"
#include "lib/block/block.h"
#include "lib/chunk/chunk.h"

#include "lib/window/window.h"
#include "lib/game/game.h"

#include "lib/objects/cube.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

bool firstMouse = true;

int main() {
    Game game{};

    //
    // // Load textures
    Texture diamondTexture("/home/piotr/Development/C++/Minecraft/src/assets/textures/diamond_block.png", GL_RGBA);
    Texture dirtTexture("/home/piotr/Development/C++/Minecraft/src/assets/textures/dirt.png", GL_RGBA);

    Texture bottomTexture("/home/piotr/Development/C++/Minecraft/src/assets/textures/bottom.png", GL_RGBA);
    Texture topTexture("/home/piotr/Development/C++/Minecraft/src/assets/textures/top.png", GL_RGBA);
    Texture leftTexture("/home/piotr/Development/C++/Minecraft/src/assets/textures/left.png", GL_RGBA);
    Texture rightTexture("/home/piotr/Development/C++/Minecraft/src/assets/textures/right.png", GL_RGBA);
    Texture backTexture("/home/piotr/Development/C++/Minecraft/src/assets/textures/back.png", GL_RGBA);
    Texture frontTexture("/home/piotr/Development/C++/Minecraft/src/assets/textures/front.png", GL_RGBA);
    //
    //
    //
    // generateChunks();
    //
    // while (!glfwWindowShouldClose(window))
    // {
    //     shader.use();
    //     glm::mat4 projection = glm::perspective(45.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    //     shader.setMat4("projection", projection);
    //
    //     glm::mat4 view = player.camera.GetViewMatrix();
    //     shader.setMat4("view", view);
    //
    //     vbo.Bind();
    //     vao.Bind();
    //
    //     for (int i = 0; i < RENDER_CHUNKS; i++)
    //     {
    //         for (int j = 0; j < RENDER_CHUNKS; j++)
    //         {
    //             Chunk chunk = chunks[i][j];
    //             Chunk *backChunk = nullptr;
    //             Chunk *rightChunk = nullptr;
    //
    //             if (i - 1 > 0)
    //             {
    //                 backChunk = &chunks[i - 1][j];
    //                 std::cout << "TEst" << std::endl;
    //             }
    //
    //             if(i < RENDER_CHUNKS) {
    //                 rightChunk = &chunks[i+1][j];
    //             }
    //
    //
    //             // if (backChunk != nullptr)
    //             // {
    //             //     std::cout << backChunk.blocks[0][0][0].Type << std::endl;
    //             // }
    //
    //             for (int x = 0; x < CHUNK_WIDTH; x++)
    //             {
    //                 for (int y = 0; y < CHUNK_HEIGHT; y++)
    //                 {
    //                     for (int z = 0; z < CHUNK_WIDTH; z++)
    //                     {
    //                         if (chunk.blocks[x][y][z].Type == AIR)
    //                             continue;
    //                         if (chunk.blocks[x][y][z].Type == DIRT)
    //                             dirtTexture.use(0);
    //                         if (chunk.blocks[x][y][z].Type == DIAMOND)
    //                             diamondTexture.use(0);
    //
    //                         glm::mat4 model = glm::mat4(1.0f);
    //                         model = glm::translate(model, chunk.blocks[x][y][z].Position);
    //                         shader.setMat4("model", model);
    //
    //                         // back face
    //                         if (z == 0 || (z != 0 && chunk.blocks[x][y][z - 1].Type == AIR))
    //                         {
    //                             // TODO
    //                             // if (z == CHUNK_WIDTH - 1 && backChunk != nullptr)
    //                             // {
    //                             backTexture.use(0);
    //                             glDrawArrays(GL_TRIANGLES, 0, 6);
    //                             // }
    //                         }
    //
    //                         // front face
    //                         if (z == CHUNK_WIDTH - 1 || (z != CHUNK_WIDTH - 1 && chunk.blocks[x][y][z + 1].Type == AIR))
    //                         {
    //                             frontTexture.use(0);
    //                             glDrawArrays(GL_TRIANGLES, 6, 6);
    //                         }
    //
    //                         // left face
    //                         if (x == 0 || (x != 0 && chunk.blocks[x - 1][y][z].Type == AIR))
    //                         {
    //                             leftTexture.use(0);
    //                             glDrawArrays(GL_TRIANGLES, 12, 6);
    //                         }
    //
    //                         // right face
    //                         if (x == CHUNK_WIDTH - 1 || (x != CHUNK_WIDTH - 1 && chunk.blocks[x + 1][y][z].Type == AIR))
    //                         {
    //                             bool draw = true;
    //
    //                             // if(rightChunk != nullptr && x == CHUNK_WIDTH - 1) {
    //                             //     Block b = rightChunk->blocks[0][y][z];
    //                             //     if (b.Type != BlockType::AIR) {
    //                             //         draw = false;
    //                             //     }
    //                             // }
    //
    //                             if (draw)
    //                             {
    //                                 rightTexture.use(0);
    //                                 glDrawArrays(GL_TRIANGLES, 18, 6);
    //                             }
    //                         }
    //
    //                         // bottom face
    //                         if (y == 0 || (y != 0 && chunk.blocks[x][y - 1][z].Type == AIR))
    //                         {
    //                             bottomTexture.use(0);
    //                             glDrawArrays(GL_TRIANGLES, 24, 6);
    //                         }
    //
    //                         // top face
    //                         if (y == CHUNK_HEIGHT - 1 || (y != CHUNK_HEIGHT - 1 && chunk.blocks[x][y + 1][z].Type == AIR))
    //                         {
    //                             topTexture.use(0);
    //                             glDrawArrays(GL_TRIANGLES, 30, 6);
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }
    //
    //
    //     processInput(window);
    //

    // }
    return 0;
}
