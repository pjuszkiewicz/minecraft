#ifndef RENDERER_H
#define RENDERER_H

#include "../../lib/objects/cube.h"
#include "../../lib/texture/texture.h"
#include "../../lib/map/pair_hash.h"
#include <unordered_map>

#include <vector>

const int RENDER_CHUNKS = 2;

class Renderer {
public:
    VBO *vbo;
    VAO *vao;
    Shader *shader;

    Texture *diamondTexture;
    Texture *dirtTexture;

    Texture *bottomTexture;
    Texture *topTexture;
    Texture *leftTexture;
    Texture *rightTexture;
    Texture *backTexture;
    Texture *frontTexture;

    Renderer() {
        vbo = new VBO(CubeVertices, sizeof(CubeVertices));

        vao = new VAO();
        vao->LinkAttrib(0, 3, GL_FLOAT, 5 * sizeof(float), (void *) (0));
        vao->LinkAttrib(1, 2, GL_FLOAT, 5 * sizeof(float), (void *) (3 * sizeof(float)));

        shader = new Shader("/Users/piotr/Development/C++/minecraft/src/assets/shaders/example/vertex.vs",
                            "/Users/piotr/Development/C++/minecraft/src/assets/shaders/example/fragment.fs");

        diamondTexture = new Texture("/Users/piotr/Development/C++/minecraft/src/assets/textures/diamond_block.png",
                                     GL_RGBA);
        dirtTexture = new Texture("/Users/piotr/Development/C++/minecraft/src/assets/textures/dirt.png", GL_RGBA);

        bottomTexture = new Texture("/Users/piotr/Development/C++/minecraft/src/assets/textures/bottom.png", GL_RGBA);
        topTexture = new Texture("/Users/piotr/Development/C++/minecraft/src/assets/textures/top.png", GL_RGBA);
        leftTexture = new Texture("/Users/piotr/Development/C++/minecraft/src/assets/textures/left.png", GL_RGBA);
        rightTexture = new Texture("/Users/piotr/Development/C++/minecraft/src/assets/textures/right.png", GL_RGBA);
        backTexture = new Texture("/Users/piotr/Development/C++/minecraft/src/assets/textures/back.png", GL_RGBA);
        frontTexture = new Texture("/Users/piotr/Development/C++/minecraft/src/assets/textures/front.png", GL_RGBA);
    }

    ~Renderer() {
        vbo->Delete();
        delete vbo;

        vao->Delete();
        delete vao;
    }

    void clear() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void draw(
        Player *player,
        const std::unordered_map<std::pair<int, int>, Chunk, PairHash> &chunks
    ) {
        clear();
        update_shader(player);
        draw_new_chunks(chunks);
    }

    void update_shader(Player *player) {
        shader->use();

        glm::mat4 projection = glm::perspective(45.0f, (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);
        shader->setMat4("projection", projection);

        glm::mat4 view = player->camera.GetViewMatrix();
        shader->setMat4("view", view);
    }

    void draw_new_chunks(const std::unordered_map<std::pair<int, int>, Chunk, PairHash> &chunks) const {
        vbo->Bind();
        vao->Bind();

        for (const auto &[key, value]: chunks) {
            draw_chunk(chunks, value);
        }
    }

    void draw_chunk(std::unordered_map<std::pair<int, int>, Chunk, PairHash> chunks, Chunk chunk) const {
        dirtTexture->use(0);

        for (int x = 0; x < CHUNK_WIDTH; x++) {
            for (int y = 0; y < CHUNK_HEIGHT; y++) {
                for (int z = 0; z < CHUNK_WIDTH; z++) {
                    if (chunk.blocks[x][y][z].Type == AIR) {
                        continue;
                    }

                    bool isTopColliding = y != CHUNK_HEIGHT - 1 && chunk.blocks[x][y + 1][z].Type != AIR;
                    bool isBottomColliding = y != 0 && chunk.blocks[x][y - 1][z].Type != AIR;

                    bool isLeftColliding = x != 0 && chunk.blocks[x - 1][y][z].Type != AIR;
                    if (x == 0) {
                        std::pair<int, int> key = {chunk.x - 1, chunk.z};

                        if (chunks.count(key) == 1) {
                            Chunk collidingChunk = chunks[key];

                            if (collidingChunk.blocks[CHUNK_WIDTH - 1][y][z].Type != AIR) {
                                isLeftColliding = true;
                            }
                        }
                    }

                    bool isRightColliding = x != CHUNK_WIDTH - 1 && chunk.blocks[x + 1][y][z].Type != AIR;
                    if (x == CHUNK_WIDTH - 1) {
                        std::pair<int, int> key = {chunk.x + 1, chunk.z};

                        if (chunks.count(key) == 1) {
                            Chunk collidingChunk = chunks[key];

                            if (collidingChunk.blocks[0][y][z].Type != AIR) {
                                isRightColliding = true;
                            }
                        }
                    }

                    bool isFrontColliding = z != 0 && chunk.blocks[x][y][z - 1].Type != AIR;
                    if (z == 0) {
                        std::pair<int, int> key = {chunk.x, chunk.z - 1};

                        if (chunks.count(key) == 1) {
                            Chunk collidingChunk = chunks[key];

                            if (collidingChunk.blocks[x][y][CHUNK_WIDTH - 1].Type != AIR) {
                                isFrontColliding = true;
                            }
                        }
                    }

                    bool isBackColliding = z != CHUNK_WIDTH - 1 && chunk.blocks[x][y][z + 1].Type != AIR;
                    if (z == CHUNK_WIDTH - 1) {
                        std::pair<int, int> key = {chunk.x, chunk.z + 1};

                        if (chunks.count(key) == 1) {
                            Chunk collidingChunk = chunks[key];

                            if (collidingChunk.blocks[x][y][0].Type != AIR) {
                                isBackColliding = true;
                            }
                        }
                    }

                    if (chunk.blocks[x][y][z].Type == AIR) {
                        continue;
                    }

                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::translate(model, chunk.blocks[x][y][z].Position);
                    shader->setMat4("model", model);

                    // front face
                    if (!isFrontColliding) {
                        backTexture->use(0);
                        glDrawArrays(GL_TRIANGLES, 0, 6);
                    }

                    // back face
                    if (!isBackColliding) {
                        frontTexture->use(0);
                        glDrawArrays(GL_TRIANGLES, 6, 6);
                    }

                    // left face
                    if (!isLeftColliding) {
                        leftTexture->use(0);
                        glDrawArrays(GL_TRIANGLES, 12, 6);
                    }

                    // right face
                    if (!isRightColliding) {
                        rightTexture->use(0);
                        glDrawArrays(GL_TRIANGLES, 18, 6);
                    }

                    if (!isTopColliding) {
                        topTexture->use(0);
                        glDrawArrays(GL_TRIANGLES, 30, 6);
                    }

                    if (!isBottomColliding) {
                        bottomTexture->use(0);
                        glDrawArrays(GL_TRIANGLES, 24, 6);
                    }
                }
            }
        }
    }
};

#endif //RENDERER_H
