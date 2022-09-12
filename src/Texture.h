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
	GLuint GetTexture();
	void Use();
	GLuint texture;
	float internal_format = GL_RGB, image_format = GL_RGB;
};

