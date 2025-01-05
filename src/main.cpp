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

#include "lib/objects/cube.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);
GLFWwindow *createWindow();
int loadGlad();

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

Player player(glm::vec3(0.0f, 0.0f, 0.0f));

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

const int RENDER_CHUNKS = 2;

Chunk chunks[RENDER_CHUNKS][RENDER_CHUNKS];

void generateChunks()
{
    for (int i = 0; i < RENDER_CHUNKS; i++)
    {
        for (int j = 0; j < RENDER_CHUNKS; j++)
        {
            Chunk chunk(i * CHUNK_WIDTH, j * CHUNK_WIDTH);

            for (int x = 0; x < CHUNK_WIDTH; x++)
            {
                // for (int y = 0; y < CHUNK_HEIGHT; y++)
                for (int y = 0; y < 1; y++)
                {
                    // for (int z = 0; z < CHUNK_WIDTH; z++)
                    for (int z = 0; z < 1; z++)
                    {
                        int xOffset = i * CHUNK_WIDTH;
                        int zOffset = j * CHUNK_WIDTH;

                        glm::vec3 pos(x + xOffset, y, z + zOffset);
                        Block block(DIRT, pos);
                        chunk.blocks[x][y][z] = block;
                    }
                }
            }

            chunks[i][j] = chunk;
        }
    }
}

int main()
{
    GLFWwindow *window = createWindow();

    glEnable(GL_DEPTH_TEST);

    VBO vbo(CubeVertices, sizeof(CubeVertices));
    VAO vao;
    vao.LinkAttrib(0, 3, GL_FLOAT, 5 * sizeof(float), (void *)(0));
    vao.LinkAttrib(1, 2, GL_FLOAT, 5 * sizeof(float), (void *)(3 * sizeof(float)));

    // Load textures
    Texture diamondTexture("/home/piotr/Development/C++/Minecraft/src/assets/textures/diamond_block.png", GL_RGBA);
    Texture dirtTexture("/home/piotr/Development/C++/Minecraft/src/assets/textures/dirt.png", GL_RGBA);

    Texture bottomTexture("/home/piotr/Development/C++/Minecraft/src/assets/textures/bottom.png", GL_RGBA);
    Texture topTexture("/home/piotr/Development/C++/Minecraft/src/assets/textures/top.png", GL_RGBA);
    Texture leftTexture("/home/piotr/Development/C++/Minecraft/src/assets/textures/left.png", GL_RGBA);
    Texture rightTexture("/home/piotr/Development/C++/Minecraft/src/assets/textures/right.png", GL_RGBA);
    Texture backTexture("/home/piotr/Development/C++/Minecraft/src/assets/textures/back.png", GL_RGBA);
    Texture frontTexture("/home/piotr/Development/C++/Minecraft/src/assets/textures/front.png", GL_RGBA);


    Shader shader("/home/piotr/Development/C++/Minecraft/src/assets/shaders/example/vertex.vs", "/home/piotr/Development/C++/Minecraft/src/assets/shaders/example/fragment.fs");

    generateChunks();

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        glm::mat4 projection = glm::perspective(45.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        shader.setMat4("projection", projection);

        glm::mat4 view = player.camera.GetViewMatrix();
        shader.setMat4("view", view);

        vbo.Bind();
        vao.Bind();

        for (int i = 0; i < RENDER_CHUNKS; i++)
        {
            for (int j = 0; j < RENDER_CHUNKS; j++)
            {
                Chunk chunk = chunks[i][j];
                Chunk *backChunk = nullptr;

                if (i - 1 > 0)
                {
                    backChunk = &chunks[i - 1][j];
                    std::cout << "TEst" << std::endl;
                }

                // if (backChunk != nullptr)
                // {
                //     std::cout << backChunk.blocks[0][0][0].Type << std::endl;
                // }

                for (int x = 0; x < CHUNK_WIDTH; x++)
                {
                    for (int y = 0; y < CHUNK_HEIGHT; y++)
                    {
                        for (int z = 0; z < CHUNK_WIDTH; z++)
                        {
                            if (chunk.blocks[x][y][z].Type == AIR)
                                continue;
                            if (chunk.blocks[x][y][z].Type == DIRT)
                                dirtTexture.use(0);
                            if (chunk.blocks[x][y][z].Type == DIAMOND)
                                diamondTexture.use(0);

                            glm::mat4 model = glm::mat4(1.0f);
                            model = glm::translate(model, chunk.blocks[x][y][z].Position);
                            shader.setMat4("model", model);

                            // back face
                            if (z == 0 || (z != 0 && chunk.blocks[x][y][z - 1].Type == AIR))
                            {
                                // TODO
                                // if (z == CHUNK_WIDTH - 1 && backChunk != nullptr)
                                // {
                                backTexture.use(0);
                                glDrawArrays(GL_TRIANGLES, 0, 6);
                                // }
                            }

                            // front face
                            if (z == CHUNK_WIDTH - 1 || (z != CHUNK_WIDTH - 1 && chunk.blocks[x][y][z + 1].Type == AIR))
                            {
                                frontTexture.use(0);
                                glDrawArrays(GL_TRIANGLES, 6, 6);
                            }

                            // left face
                            if (x == 0 || (x != 0 && chunk.blocks[x - 1][y][z].Type == AIR))
                            {
                                leftTexture.use(0);
                                glDrawArrays(GL_TRIANGLES, 12, 6);
                            }

                            // right face
                            if (x == CHUNK_WIDTH - 1 || (x != CHUNK_WIDTH - 1 && chunk.blocks[x + 1][y][z].Type == AIR))
                            {
                                rightTexture.use(0);
                                glDrawArrays(GL_TRIANGLES, 18, 6);
                            }

                            // bottom face
                            if (y == 0 || (y != 0 && chunk.blocks[x][y - 1][z].Type == AIR))
                            {
                                bottomTexture.use(0);
                                glDrawArrays(GL_TRIANGLES, 24, 6);
                            }

                            // top face
                            if (y == CHUNK_HEIGHT - 1 || (y != CHUNK_HEIGHT - 1 && chunk.blocks[x][y + 1][z].Type == AIR))
                            {
                                topTexture.use(0);
                                glDrawArrays(GL_TRIANGLES, 30, 6);
                            }
                        }
                    }
                }
            }
        }

        player.Update(deltaTime);

        processInput(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vbo.Delete();
    vao.Delete();

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
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

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        player.HandlePlayerMove(SPRINT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
        player.HandlePlayerMove(WALK, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        player.HandlePlayerMove(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        player.HandlePlayerMove(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        player.HandlePlayerMove(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        player.HandlePlayerMove(RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        player.HandlePlayerMove(JUMP, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

GLFWwindow *createWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Minecraft", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    loadGlad();

    return window;
}

int loadGlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    return 0;
}
