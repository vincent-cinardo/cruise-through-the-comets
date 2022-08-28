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
	Texture(const char* path);
	void Use();

private:
	GLuint texture;
};

