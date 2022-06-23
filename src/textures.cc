#include "textures.hh"
#include "errors.hh"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

int loadTexture(GLuint* textureId, const char* textureFile) {
    std::cout << "loading " << textureFile << std::endl;

    stbi_set_flip_vertically_on_load(true);

    int textureWidth = 0;
    int textureHeight = 0;
    int textureComponents = 3;
    unsigned char* texture = stbi_load(
        textureFile,
        &textureWidth,
        &textureHeight,
        &textureComponents,
        3
    );

    if (texture == nullptr) {
        CERR(BM_ERR_STBI_LOAD, BM_ERR_STBI_LOAD);
        return BM_ERR_STBI_LOAD;
    }

    glGenTextures(1, textureId);
    glBindTexture(GL_TEXTURE_2D, *textureId);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        textureWidth,
        textureHeight,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        texture
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(texture);

    return 0;
}
