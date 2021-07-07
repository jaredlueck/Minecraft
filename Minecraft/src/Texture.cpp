#include <glad/glad.h>
#include <iostream>
#include "Texture.h"
#include "stb_image.h"


void Texture::Load(const std::string& textureName)
{
    mPath = "./textures/" + textureName;

    int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true);

    unsigned char *data = stbi_load(mPath.c_str(), &width, &height, &nrChannels, 0);

	if (data) 
	{
		int format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Failed to load texture: " << mPath << std::endl;
	}
}

void Texture::Bind(unsigned int slot)
{
	glBindTextureUnit(slot, ID);
}

