#include "BackgroundRenderer.h"

BackgroundRenderer::BackgroundRenderer(Shader shader)
{
	float vertices[] = {
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,

		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_VERTEX_ARRAY, vbo);
	glBufferData(GL_VERTEX_ARRAY, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *) 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));

	this->shader = shader;
	texture = ResourceManager::GetTexture("background");
}

BackgroundRenderer::BackgroundRenderer()
{
	texture = ResourceManager::GetTexture("background");
}

void BackgroundRenderer::Render()
{
	glBindVertexArray(vao);
	shader.Use();
	glActiveTexture(GL_TEXTURE0);
	texture.Use();
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
}