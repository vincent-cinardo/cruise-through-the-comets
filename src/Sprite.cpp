#include "Sprite.h"

//Default sprite, so default buffers, shaders, and texture.
Sprite::Sprite()
{
	x = 0;
	y = 0;

	float vertices[] = {   //Here are texture coords
		0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f
	};

	int indices[] = {
		1, 0, 2,
		1, 3, 2
	};

	//Remember to gen/bind vao first, then set vertex attributes after binding buffers.

	shader = Shader::Shader(".\\default.vert", ".\\default.frag");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	//Should I be putting this here? Answer then unncomment
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

	texture = Texture::Texture(".\\textures\\stick.png", true);
	shaderPtr = &shader;
	texturePtr = &texture;
}

//Default sprite, so default buffers, shaders, and texture.
/*Sprite::Sprite(float x, float y, const char* location)
{
	x = 0;
	y = 0;

	float vertices[] = {   //Here are texture coords
		0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f
	};

	int indices[] = {
		1, 0, 2,
		1, 3, 2
	};

	//Remember to gen/bind vao first, then set vertex attributes after binding buffers.

	shader = Shader::Shader(".\\default.vert", ".\\default.frag");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	texture = Texture::Texture(".\\textures\\dog.png");
	shaderPtr = &shader;
	texturePtr = &texture;
}*/

Sprite::~Sprite()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	shaderPtr->~Shader();
}

void Sprite::Move(float x, float y)
{
	this->x += x;
	this->y += y;
}

void Sprite::Draw()
{
	shader.Use();
	texture.Use();
	shader.SetModel(x, y);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	//glBindVertexArray(0);
}

unsigned int Sprite::GetProgram()
{
	return shader.GetProgram();
}