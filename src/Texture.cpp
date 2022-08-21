#include "Texture.h"

Texture::Texture()
{
	texture = 0;
}

Texture::Texture(const char* path)
{
	int x, y, comp;
	unsigned char* image = stbi_load(path, &x, &y, &comp, 0);

	texture = 0;

	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Error: Failed to load texture." << std::endl;
	}
	stbi_image_free(image);
}

void Texture::Use()
{
	glBindTexture(GL_TEXTURE_2D, texture);
}