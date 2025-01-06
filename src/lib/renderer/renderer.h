#ifndef RENDERER_H
#define RENDERER_H

#include "../../lib/objects/cube.h"
#include "../../lib/texture/texture.h"
#include "../../lib/map/pair_hash.h"
#include <unordered_map>

#include <vector>

const int RENDER_DISTANCE = 4;

// const std::string assetsPath = "/Users/piotr/Development/C++/minecraft/src/assets";
const std::string assetsPath = "/home/piotr/Development/C++/Minecraft/src/assets";

class Renderer {
public:
    unsigned int instanceVBO, quadVAO, quadVBO;

    VBO *vbo;
    // VBO *instanceVBO;
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
        glm::vec3 *cubePositions = new glm::vec3[1000000];

        int i = 0;
        for (int z = 0; z < 100; z++) {
            for (int y = 0; y < 100; y++) {
                for (int x = 0; x < 100; x++) {
                    cubePositions[i] = glm::vec3((float) x, (float) y, (float) z);
                    i++;
                }
            }
        }

        glGenBuffers(1, &instanceVBO);
        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 1000000, &cubePositions[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices), CubeVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
        // also set instance data
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO); // this attribute comes from a different vertex buffer
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glVertexAttribDivisor(2, 1);

        //
        // vao = new VAO();
        // vao->Bind();
        //
        // vbo = new VBO(CubeVertices, sizeof(CubeVertices));
        // vbo->Bind();
        //
        // vao->LinkAttrib(0, 3, GL_FLOAT, 5 * sizeof(float), (void *) (0));
        // vao->LinkAttrib(1, 2, GL_FLOAT, 5 * sizeof(float), (void *) (3 * sizeof(float)));
        //
        // vbo->Unbind();
        //
        // glEnableVertexAttribArray(2);
        //
        // unsigned int buffer;
        // glGenBuffers(1, &buffer);
        // glBindBuffer(GL_ARRAY_BUFFER, buffer);
        // glBufferData(GL_ARRAY_BUFFER, 1000 * sizeof(glm::mat3), &cubePositions[0], GL_STATIC_DRAW);
        // glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) (0));
        // glVertexAttribDivisor(2, 1);

        shader = new Shader((assetsPath + "/shaders/example/vertex.vs").c_str(),
                            (assetsPath + "/shaders/example/fragment.fs").c_str());

        diamondTexture = new Texture((assetsPath + "/textures/diamond_block.png").c_str(),
                                     GL_RGBA);
        dirtTexture = new Texture((assetsPath + "/textures/dirt.png").c_str(), GL_RGB);

        bottomTexture = new Texture((assetsPath + "/textures/bottom.png").c_str(), GL_RGBA);
        topTexture = new Texture((assetsPath + "/textures/top.png").c_str(), GL_RGBA);
        leftTexture = new Texture((assetsPath + "/textures/left.png").c_str(), GL_RGBA);
        rightTexture = new Texture((assetsPath + "/textures/right.png").c_str(), GL_RGBA);
        backTexture = new Texture((assetsPath + "/textures/back.png").c_str(), GL_RGBA);
        frontTexture = new Texture((assetsPath + "/textures/front.png").c_str(), GL_RGBA);
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
        // draw_new_chunks(chunks, player);
        draw_test();
    }

    void draw_test() {
        // vbo->Bind();

        dirtTexture->use(0);


        // vao->Bind();

        glBindVertexArray(quadVAO);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 1000000);

        vao->Unbind();
    }

    void update_shader(Player *player) {
        shader->use();

        glm::mat4 projection = glm::perspective(45.0f, (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);
        shader->setMat4("projection", projection);

        glm::mat4 view = player->camera.GetViewMatrix();
        shader->setMat4("view", view);
    }

    void draw_new_chunks(const std::unordered_map<std::pair<int, int>, Chunk, PairHash> &chunks, Player *player) const {
        vbo->Bind();
        vao->Bind();

        float playerX = player->Position.x / CHUNK_WIDTH;
        float playerZ = player->Position.z / CHUNK_WIDTH;

        for (int i = playerX - RENDER_DISTANCE; i <= playerX + RENDER_DISTANCE; i++) {
            for (int j = playerZ - RENDER_DISTANCE; j <= playerZ + RENDER_DISTANCE; j++) {
                auto it = chunks.find(std::make_pair(i, j));
                if (it != chunks.end()) {
                    const Chunk &chunk = it->second;
                    draw_chunk(chunks, chunk);
                }

                // if (chunks.count(std::make_pair(i, j)) != 0) {
                //     Chunk chunk = chunks.at(std::make_pair(i, j));
                //     draw_chunk(chunks, chunk);
                // }
            }
        }
    }

    void draw_chunk(const std::unordered_map<std::pair<int, int>, Chunk, PairHash> &chunks, const Chunk &chunk) const {
        dirtTexture->use(0);
        for (int x = 0; x < CHUNK_WIDTH; x++) {
            for (int y = 0; y < CHUNK_HEIGHT; y++) {
                for (int z = 0; z < CHUNK_WIDTH; z++) {
                    if (chunk.blocks[x][y][z] == 0) {
                        continue;
                    }

                    bool isTopColliding = y != CHUNK_HEIGHT - 1 && chunk.blocks[x][y + 1][z] != 0;
                    bool isBottomColliding = y != 0 && chunk.blocks[x][y - 1][z] != 0;

                    bool isLeftColliding = x != 0 && chunk.blocks[x - 1][y][z] != 0;
                    if (x == 0) {
                        auto it = chunks.find(std::make_pair(chunk.x - 1, chunk.z));

                        if (it != chunks.end()) {
                            const Chunk &collidingChunk = it->second;

                            if (collidingChunk.blocks[CHUNK_WIDTH - 1][y][z] != 0) {
                                isLeftColliding = true;
                            }
                        }
                    }

                    bool isRightColliding = x != CHUNK_WIDTH - 1 && chunk.blocks[x + 1][y][z] != 0;
                    if (x == CHUNK_WIDTH - 1) {
                        auto it = chunks.find(std::make_pair(chunk.x + 1, chunk.z));

                        if (it != chunks.end()) {
                            const Chunk &collidingChunk = it->second;

                            if (collidingChunk.blocks[0][y][z] != 0) {
                                isRightColliding = true;
                            }
                        }
                    }

                    bool isFrontColliding = z != 0 && chunk.blocks[x][y][z - 1] != 0;
                    if (z == 0) {
                        auto it = chunks.find(std::make_pair(chunk.x, chunk.z - 1));

                        if (it != chunks.end()) {
                            const Chunk &collidingChunk = it->second;

                            if (collidingChunk.blocks[x][y][CHUNK_WIDTH - 1] != 0) {
                                isFrontColliding = true;
                            }
                        }
                    }

                    bool isBackColliding = z != CHUNK_WIDTH - 1 && chunk.blocks[x][y][z + 1] != 0;
                    if (z == CHUNK_WIDTH - 1) {
                        auto it = chunks.find(std::make_pair(chunk.x, chunk.z + 1));

                        if (it != chunks.end()) {
                            const Chunk &collidingChunk = it->second;

                            if (collidingChunk.blocks[x][y][0] != 0) {
                                isBackColliding = true;
                            }
                        }
                    }

                    if (chunk.blocks[x][y][z] == 0) {
                        continue;
                    }

                    glm::mat4 model = glm::mat4(1.0f);
                    float block_x = chunk.x * CHUNK_WIDTH + x;
                    float block_z = chunk.z * CHUNK_WIDTH + z;
                    model = glm::translate(model, glm::vec3(block_x, y, block_z));
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
