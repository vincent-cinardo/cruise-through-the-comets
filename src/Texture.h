#pragma once
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "stb_image.h"

#pragma once
class Texture
{
public:
	Texture();
	~Texture();
	Texture(const char* path, bool alpha);
	unsigned int GetTexture();
	void Use();
	unsigned int texture;
	float internal_format, image_format;
	const char* filepath;
};

