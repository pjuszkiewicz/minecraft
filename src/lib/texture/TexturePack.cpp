//
// Created by Piotr Juszkiewicz on 09/01/2025.
//

#include "./TexturePack.h"

glm::vec2 TexturePack::getUVForBlock(int blockID, int ui, int vi) {
    int blocksPerRow = 256 / 32; // np. BLOCK_SIZE = 16
    int row = blockID / blocksPerRow;
    int col = blockID % blocksPerRow;

    // Dolny lewy róg tekstury w atlasie
    float u = (float) ui / blocksPerRow;
    float v = (float) vi / blocksPerRow;

    // Rozmiar pojedynczej tekstury w atlasie
    float uvWidth = 1.0f / blocksPerRow;

    return glm::vec2(u, v);
}
