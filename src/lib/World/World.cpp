#include "World.h"

#define STB_PERLIN_IMPLEMENTATION
#include "../../../vendor/stb_perlin.h"

bool World::isBlockAt(glm::vec3 pos) {
    int chunkX = static_cast<int>(floor(pos.x / CHUNK_WIDTH));
    int chunkZ = static_cast<int>(floor(pos.z / CHUNK_WIDTH));

    auto chunkIndex = chunks.find(std::make_pair(chunkX, chunkZ));
    if (chunkIndex != chunks.end()) {
        Chunk &chunk = chunkIndex->second;

        int x = static_cast<int>(floor(pos.x)) - (chunkX * CHUNK_WIDTH);
        int y = static_cast<int>(floor(pos.y));
        int z = static_cast<int>(floor(pos.z)) - (chunkZ * CHUNK_WIDTH);

        return chunk.blocks[x][y][z].type != BlockType::AIR;
    }

    return false;
}


void World::removeBlockAt(glm::vec3 pos) {
    int chunkX = static_cast<int>(floor(pos.x / CHUNK_WIDTH));
    int chunkZ = static_cast<int>(floor(pos.z / CHUNK_WIDTH));

    auto chunkIndex = chunks.find(std::make_pair(chunkX, chunkZ));
    if (chunkIndex != chunks.end()) {
        Chunk &chunk = chunkIndex->second;

        int x = static_cast<int>(floor(pos.x)) - (chunkX * CHUNK_WIDTH);
        int y = static_cast<int>(floor(pos.y));
        int z = static_cast<int>(floor(pos.z)) - (chunkZ * CHUNK_WIDTH);

        chunk.blocks[x][y][z].type = BlockType::AIR;
    }
}

void World::placeBlockAt(glm::vec3 pos) {
    int chunkX = static_cast<int>(floor(pos.x / CHUNK_WIDTH));
    int chunkZ = static_cast<int>(floor(pos.z / CHUNK_WIDTH));

    auto chunkIndex = chunks.find(std::make_pair(chunkX, chunkZ));
    if (chunkIndex != chunks.end()) {
        Chunk &chunk = chunkIndex->second;

        int x = static_cast<int>(floor(pos.x)) - (chunkX * CHUNK_WIDTH);
        int y = static_cast<int>(floor(pos.y));
        int z = static_cast<int>(floor(pos.z)) - (chunkZ * CHUNK_WIDTH);

        chunk.blocks[x][y][z].type = BlockType::ACACIA_PLANKS;
        int px = static_cast<int>(floor(pos.x));
        int py = static_cast<int>(floor(pos.y));
        int pz = static_cast<int>(floor(pos.z));
        chunk.blocks[x][y][z].position = glm::vec3(px, py, pz);

    }
}

float perlinNoise(float x, float z, int octaves, float persistence, float scale) {
    float noise = 0.0f;
    float amplitude = 1.0f;
    float frequency = 1.0f;
    float maxValue = 0.0f;

    for (int i = 0; i < octaves; i++) {
        noise += amplitude * stb_perlin_noise3(x * frequency * scale, 0.0f, z * frequency * scale, 0, 0, 0);
        maxValue += amplitude;

        amplitude *= persistence;
        frequency *= 2.0f;
    }

    return noise / maxValue; // Normalizuj wynik do zakresu 0-1
}

void World::generateChunks() {
    int lastTreeX = 0;
    int lastTreeZ = 0;
    for (int x = -20; x <= 20; x++) {
        for (int z = -20; z <= 20; z++) {
            Chunk chunk(x, z);

            int chunkX = x * CHUNK_WIDTH;
            int chunkZ = z * CHUNK_WIDTH;

            bool hasTree = false;

            for (int bx = 0; bx < CHUNK_WIDTH; bx++) {
                for (int bz = 0; bz < CHUNK_WIDTH; bz++) {
                    float scale = 0.007;

                    float noise = perlinNoise((chunkX + bx), (chunkZ + bz), 3, 5, scale) + 0.5;
                    float noise1 = perlinNoise((chunkX + bx), (chunkZ + bz), 3, 5, 0.001) + 0.5;
                    if (noise < 0.0f) noise = 0.0;
                    if (noise1 < 0.0f) noise1 = 0.0;

                    int height = (int) (noise * noise1 * 64);

                    int xOffset = x * CHUNK_WIDTH;
                    int zOffset = z * CHUNK_WIDTH;

                    for (int by = 0; by < height + 1; by++) {
                        glm::vec3 pos(bx + xOffset, by, bz + zOffset);
                        BlockType type = BlockType::DIRT;

                        if (by < height - 1) {
                            type = BlockType::STONE;
                        }

                        Block block(type, pos);

                        chunk.blocks[bx][by][bz] = block;
                    }


                    // drzwa
                    bool addTree = perlinNoise((chunkX + bx), (chunkZ + bz), 3, 0, scale) + 0.5 > 0.9;
                    if (addTree && !hasTree) {
                        hasTree = true;
                        if (abs(lastTreeX - x) > 5 && abs(lastTreeZ - z) > 5) {
                            for (int i = 0; i < 5; i++) {
                                glm::vec3 pos(bx + xOffset, height + i, bz + zOffset);
                                Block block(ACACIA_WOOD, pos);
                                chunk.blocks[bx][height + i][bz] = block;
                            }

                            lastTreeX = bx + xOffset;
                            lastTreeZ = bz + zOffset;
                        }
                    }
                }
            }

            chunks[{x, z}] = chunk;
        }
    }
}
