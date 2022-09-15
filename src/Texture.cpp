#include "Texture.h"

Texture::Texture()
{

}

Texture::~Texture()
{
	glDeleteTextures(1, &this->texture);
}

Texture::Texture(const char* path, bool alpha)
{
	filepath = path;
	int x, y, comp;
	unsigned char* image = stbi_load(path, &x, &y, &comp, 0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	std::cout << "Texture value assgined " << texture << std::endl;

	if (alpha)
	{
		internal_format = GL_RGBA;
		image_format = GL_RGBA;
	}
	else
	{
		internal_format = GL_RGB;
		image_format = GL_RGB;
	}

	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internal_format, x, y, 0, image_format, GL_UNSIGNED_BYTE, image);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Error: Failed to load texture." << std::endl;
	}
	stbi_image_free(image);
}

unsigned int Texture::GetTexture()
{
	return texture;
}

void Texture::Use()
{
	std::cout << "The filepath for the texture is: " << filepath << std::endl;
	glBindTexture(GL_TEXTURE_2D, texture);
}

