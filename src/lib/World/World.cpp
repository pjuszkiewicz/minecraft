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

        std::cout << x << " " << y << " " << z << std::endl;
        return chunk.blocks[x][y][z].type != BlockType::AIR;
    }

    return false;
}


void World::removeBlockAt(glm::vec3 pos) {
    // int chunkWorldX = pos.x - ((int) pos.x % CHUNK_WIDTH);
    // int chunkWorldZ = pos.z - ((int) pos.z % CHUNK_WIDTH);

    int chunkX = static_cast<int>(floor(pos.x / CHUNK_WIDTH));
    int chunkZ = static_cast<int>(floor(pos.z / CHUNK_WIDTH));

    // int chunkX = chunkWorldX / CHUNK_WIDTH;
    // int chunkZ = chunkWorldZ / CHUNK_WIDTH;

    auto chunkIndex = chunks.find(std::make_pair(chunkX, chunkZ));
    if (chunkIndex != chunks.end()) {
        Chunk &chunk = chunkIndex->second;

        int x = static_cast<int>(floor(pos.x)) - (chunkX * CHUNK_WIDTH);
        int y = static_cast<int>(floor(pos.y));
        int z = static_cast<int>(floor(pos.z)) - (chunkZ * CHUNK_WIDTH);

        std::cout << x << " " << y << " " << z << std::endl;
        chunk.blocks[x][y][z].type = BlockType::AIR;
    }
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
        frequency *= 2.0f; // Zwiększ częstotliwość
    }

    return noise / maxValue; // Normalizuj wynik do zakresu 0-1
}

void World::generateChunks() {
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

                    int height = (int) (noise * 5);


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
