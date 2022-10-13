#include "MenuRenderer.h"

MenuRenderer::MenuRenderer()
{

}

MenuRenderer::MenuRenderer(Shader shader)
{
	float vertices[] = {   //Here are texture coords
		0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	   -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	   -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	   -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	};

	shader = Shader::Shader(".\\UI.vert", ".\\UI.frag");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	this->shader = shader;
	texture = Texture::Texture(".\\textures\\retry.png", true);
}

MenuRenderer::~MenuRenderer()
{

}

void MenuRenderer::SetMenu(const char *menuName)
{
	texture = Texture::Texture(menuName, false);
}