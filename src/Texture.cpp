#include <glad/glad.h>
#include "Texture.h"
#include "stb_image.h"


Texture::Texture(const std::string& textureName)
{
    std::string texturePath = "/textures/" + textureName;

    int width, height, nrChannels;

    unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexImage2D(GL_TEXTURE_2D, )
}

