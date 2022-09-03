#pragma once
#include "Shader.h"
#include "Texture.h"

class Ground
{
public:
	Ground();
	~Ground();

	void Draw();
	

private:
	GLuint vao, vbo, ebo;
	Shader *shaderPtr, shader;
	Texture *texturePtr, texture;
};

