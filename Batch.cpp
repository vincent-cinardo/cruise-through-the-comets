#include "Batch.h"

//The default batch loads a single quad with default shaders.
Batch::Batch()
{
	float vertices[] = {
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};

	int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	shader = Shader::Shader(".\\default.vert", ".\\default.frag");

	vao = VAO::VAO();
	vbo = VBO::VBO(vertices, sizeof(vertices));
	ebo = EBO::EBO(indices, sizeof(indices));

	vao.Enable(0);
	vao.SetAttribute(0, 5 * sizeof(float), 0);
	vao.Enable(1);
	vao.SetAttribute(1, 5 * sizeof(float), 3);

	//shader.SetMat4("view", );

	texture = Texture::Texture(".\\textures\\grass.png", false);
}

Batch::~Batch()
{
	vao.~VAO();
	vbo.~VBO();
	ebo.~EBO();
	texture.~Texture();
	shader.~Shader();
}

void Batch::Bind()
{
	shader.Use();
	texture.Use();
	vao.Bind();
}