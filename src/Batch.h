#pragma once
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Shader.h"
#include "Texture.h"

class Batch
{
public:
	Batch();
	~Batch();
	void Bind();
	VAO vao;
	VBO vbo;
	EBO ebo;
	Shader shader;
	Texture texture;
};

