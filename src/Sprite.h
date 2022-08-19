#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"

#pragma once
class Sprite
{
public:
	Sprite();
	~Sprite();
	void Draw();

private:
	GLuint vao, vbo, ebo;
	float x, y;
};

