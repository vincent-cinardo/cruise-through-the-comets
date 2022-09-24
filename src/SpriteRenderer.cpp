#include "SpriteRenderer.h"

//Default sprite, so default buffers, shaders, and texture.
SpriteRenderer::SpriteRenderer()
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

//New constructor to be tested. Might need to pass by reference?
SpriteRenderer::SpriteRenderer(Shader shader)
{
	this->shader = shader;
	x = 0;
	y = 0;
	this->Init();
}

void SpriteRenderer::Init()
{
	x = 0;
	y = 0;

	float vertices[] = {   //Here are texture coords
		0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	shaderPtr->~Shader();
}

void SpriteRenderer::Move(float x, float y)
{
	this->x += x;
	this->y += y;
}

void SpriteRenderer::Draw()
{
	shader.Use();
	texture.Use();
	shader.SetModel(x, y);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

//New draw call to be tested; works, moving on to spritesheet
void SpriteRenderer::Draw(Texture &texture, glm::vec3 position)
{
	shader.Use();	
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	shader.SetMat4("model", model);
	
	glActiveTexture(GL_TEXTURE0);
	texture.Use(); 
	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

//Newest draw call, drawing from a sprite sheet
void SpriteRenderer::Draw(Texture& texture, glm::vec3 position, glm::vec2 bottomleft)
{
	shader.Use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	shader.SetMat4("model", model);

	glActiveTexture(GL_TEXTURE0);
	texture.Use();
	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

unsigned int SpriteRenderer::GetProgram()
{
	return shader.GetProgram();
}