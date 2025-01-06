#ifndef RENDERER_H
#define RENDERER_H

#include "../../lib/texture/texture.h"
#include "../../lib/map/pair_hash.h"
#include "../../lib/shader/shader.h"
#include "../../lib/player/player.h"
#include "../../lib/chunk/chunk.h"
#include <unordered_map>

#include <vector>

#include "../mesh/mesh.h"

const int RENDER_DISTANCE = 4;

const std::string assetsPath = "/Users/piotr/Development/C++/minecraft/src/assets";
// const std::string assetsPath = "/home/piotr/Development/C++/Minecraft/src/assets";

class Renderer {
public:
    Shader *shader;

    Texture *diamondTexture;
    Texture *dirtTexture;

    Texture *bottomTexture;
    Texture *topTexture;
    Texture *leftTexture;
    Texture *rightTexture;
    Texture *backTexture;
    Texture *frontTexture;

    Texture *texturePack;

    Mesh *mesh;

    bool changed = false;

    Renderer() {
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

        texturePack = new Texture((assetsPath + "/textures/texturepack.png").c_str(), GL_RGBA);
        mesh = new Mesh();
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

        if (!changed) {
            draw_new_chunks(chunks, player);
            changed = true;
        }

        dirtTexture->use(0);
        mesh->draw();
    }

    void update_shader(Player *player) {
        shader->use();

        glm::mat4 projection = glm::perspective(45.0f, (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);
        shader->setMat4("projection", projection);

        glm::mat4 view = player->camera.GetViewMatrix();
        shader->setMat4("view", view);
    }

    void draw_new_chunks(const std::unordered_map<std::pair<int, int>, Chunk, PairHash> &chunks, Player *player) const {
        std::vector<glm::vec3> *positions = new std::vector<glm::vec3>();

        int count = 0;

        float playerX = player->Position.x / CHUNK_WIDTH;
        float playerZ = player->Position.z / CHUNK_WIDTH;

        for (int i = playerX - RENDER_DISTANCE; i <= playerX + RENDER_DISTANCE; i++) {
            for (int j = playerZ - RENDER_DISTANCE; j <= playerZ + RENDER_DISTANCE; j++) {

                auto it = chunks.find(std::make_pair(i, j));
                if (it != chunks.end()) {
                    const Chunk &chunk = it->second;

                    // chunk
                    for (int x = 0; x < 1; x++) {
                        for (int y = 15; y < CHUNK_HEIGHT; y++) {
                            for (int z = 0; z < 1; z++) {

                                if (chunk.blocks[x][y][z].type == BlockType::AIR) {
                                    continue;
                                }

                                float bx = (i * CHUNK_WIDTH) + x;
                                float bz = (j * CHUNK_WIDTH) + z;

                                positions->push_back(glm::vec3(bx, y, bz));
                                count++;
                            }
                        }
                    }
                }
            }
        }
        std::cout << positions->size() << std::endl;
        mesh->setPositions(positions);
    }

    void draw_chunk(const std::unordered_map<std::pair<int, int>, Chunk, PairHash> &chunks, const Chunk &chunk) const {
        dirtTexture->use(0);
        for (int x = 0; x < CHUNK_WIDTH; x++) {
            for (int y = 0; y < CHUNK_HEIGHT; y++) {
                for (int z = 0; z < CHUNK_WIDTH; z++) {
                    if (chunk.blocks[x][y][z].type == BlockType::AIR) {
                        continue;
                    }

                    bool isTopColliding = y != CHUNK_HEIGHT - 1 && chunk.blocks[x][y + 1][z].type != BlockType::AIR;
                    bool isBottomColliding = y != 0 && chunk.blocks[x][y - 1][z].type != BlockType::AIR;

                    bool isLeftColliding = x != 0 && chunk.blocks[x - 1][y][z].type != BlockType::AIR;
                    if (x == 0) {
                        auto it = chunks.find(std::make_pair(chunk.x - 1, chunk.z));

                        if (it != chunks.end()) {
                            const Chunk &collidingChunk = it->second;

                            if (collidingChunk.blocks[CHUNK_WIDTH - 1][y][z].type != BlockType::AIR) {
                                isLeftColliding = true;
                            }
                        }
                    }

                    bool isRightColliding = x != CHUNK_WIDTH - 1 && chunk.blocks[x + 1][y][z].type != BlockType::AIR;
                    if (x == CHUNK_WIDTH - 1) {
                        auto it = chunks.find(std::make_pair(chunk.x + 1, chunk.z));

                        if (it != chunks.end()) {
                            const Chunk &collidingChunk = it->second;

                            if (collidingChunk.blocks[0][y][z].type != BlockType::AIR) {
                                isRightColliding = true;
                            }
                        }
                    }

                    bool isFrontColliding = z != 0 && chunk.blocks[x][y][z - 1].type != BlockType::AIR;
                    if (z == 0) {
                        auto it = chunks.find(std::make_pair(chunk.x, chunk.z - 1));

                        if (it != chunks.end()) {
                            const Chunk &collidingChunk = it->second;

                            if (collidingChunk.blocks[x][y][CHUNK_WIDTH - 1].type != BlockType::AIR) {
                                isFrontColliding = true;
                            }
                        }
                    }

                    bool isBackColliding = z != CHUNK_WIDTH - 1 && chunk.blocks[x][y][z + 1].type != BlockType::AIR;
                    if (z == CHUNK_WIDTH - 1) {
                        auto it = chunks.find(std::make_pair(chunk.x, chunk.z + 1));

                        if (it != chunks.end()) {
                            const Chunk &collidingChunk = it->second;

                            if (collidingChunk.blocks[x][y][0].type != BlockType::AIR) {
                                isBackColliding = true;
                            }
                        }
                    }

                    if (chunk.blocks[x][y][z].type == BlockType::AIR) {
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
