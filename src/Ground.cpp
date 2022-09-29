#include "Ground.h"

Ground::Ground() 
{
	float vertices[] = {
		//Grass block 1
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f

		//Grass block 2
		 //1.0f, -1.0f, 0.0f, 0.0f, 0.0f, //bottom left 4
		 //2.0f, -1.0f, 0.0f, 1.0f, 0.0f, //bottom right 5
		 //2.5f,  1.0f, 0.0f, 1.0f, 1.0f, //top right 6 
		 //1.0f,  1.0f, 0.0f, 0.0f, 1.0f, //top left 7
	};
	std::cout << "TEST" << std::endl;
	int indices[] = {
		0, 1, 3,
		1, 2, 3
		//4, 5, 6,
		//4, 7, 6
	};

	shader = Shader::Shader(".\\ground.vert", ".\\ground.frag");

	//Set up view and projection here?
	//shader.SetMat4("transform", glm::mat4(1.0f));
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_VERTEX_ARRAY, vbo);
	glBufferData(GL_VERTEX_ARRAY, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	texture = Texture::Texture(".\\textures\\grass.png", false);
	shaderPtr = &shader;
	texturePtr = &texture;
}

Ground::~Ground() 
{
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteVertexArrays(1, &vao);
	shaderPtr->~Shader();
	texturePtr->~Texture();
}

void Ground::Draw()
{
	shaderPtr->Use();
	texturePtr->Use();
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//glDrawArrays(GL_TRIANGLES, 0, sizeof(25));
	//glBindVertexArray(0);
}
