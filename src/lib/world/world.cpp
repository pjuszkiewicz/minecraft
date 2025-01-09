#include "World.h"

// #define STB_PERLIN_IMPLEMENTATION
// #include "../stb_perlin.h"

const int CHUNK_WIDTH = 16;  // Rozmiar chunku
const int CHUNK_HEIGHT = 128; // Maksymalna wysokość chunku
const float NOISE_SCALE = 0.1f; // Skalowanie szumu (im mniejsza wartość, tym większe szczegóły)
const int WORLD_WIDTH = 100;   // Szerokość świata

std::vector<std::vector<int>> World::generateTerrain(int worldWidth, int chunkHeight, float scale) {
    std::vector<std::vector<int>> heightMap(worldWidth, std::vector<int>(worldWidth));

    for (int x = 0; x < worldWidth; x++) {
        for (int z = 0; z < worldWidth; z++) {
            // Obliczanie wartości Perlin Noise
            // float noise = stb_perlin_noise3(x * scale, 0.0f, z * scale, 0, 0, 0);
            // noise = (noise + 1.0f) / 2.0f; // Skalowanie wartości od -1,1 do 0,1
            // heightMap[x][z] = static_cast<int>(noise * chunkHeight); // Skalowanie wysokości
        }
    }

    return heightMap;
}