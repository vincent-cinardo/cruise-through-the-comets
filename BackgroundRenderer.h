#pragma once
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Texture.h"
#include "Shader.h"
#include "ResourceManager.h"

class BackgroundRenderer
{
public:
	BackgroundRenderer(Shader shader);
	BackgroundRenderer();
	void Render();
private:
	Shader shader;
	Texture texture;
	GLuint vao, vbo;
};

