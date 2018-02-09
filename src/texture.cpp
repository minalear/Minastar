//
// Created by Trevor Fisher on 1/19/2018.
//

#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"
#include "glad/glad.h"

minalear::texture::texture(const char* filePath) {
    unsigned char *data = stbi_load(filePath, &width, &height, &nBits, STBI_rgb_alpha);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);
}

int minalear::texture::getWidth() {
    return width;
}
int minalear::texture::getHeight() {
    return height;
}
void minalear::texture::bind() {
    glBindTexture(GL_TEXTURE_2D, textureID);
}