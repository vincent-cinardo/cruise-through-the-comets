#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "Texture.h"

#pragma once
class Sprite
{
public:
	Sprite();
	~Sprite();
	void Draw();

private:
	GLuint vao, vbo, ebo;
	Shader shader, *shaderPtr;
	Texture texture, *texturePtr;
	float x, y;
};

