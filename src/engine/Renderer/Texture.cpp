//
// Created by piotr on 07.01.25.
//

#include "../Renderer/Texture.h"

Texture::Texture(const char *path, int format) {
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

    glGenTextures(1, &ID);

    glBindTexture(GL_TEXTURE_2D, ID);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

void Texture::use(int textureUnit) const {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

glm::vec2 Texture::getUVForBlock(int blockID, int ui, int vi) {
    int blocksPerRow = 256 / 32; // np. BLOCK_SIZE = 16
    // int row = blockID / blocksPerRow;
    // int col = blockID % blocksPerRow;

    // Dolny lewy róg tekstury w atlasie
    float u = (float) ui / blocksPerRow;
    float v = (float) vi / blocksPerRow;

    // Rozmiar pojedynczej tekstury w atlasie
    float uvWidth = 1.0f / blocksPerRow;

    return glm::vec2(u, v);
}
