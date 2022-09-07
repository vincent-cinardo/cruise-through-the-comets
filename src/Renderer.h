#pragma once
#include <iostream>
#include <array>
#include <vector>
#include <malloc.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Renderer
{
public:

	struct Vertex
	{
		float position[3];
		float texCoords[2];
		//float texture; //wouldn't make sense here?!
	};

	struct Batch
	{
		std::array<Vertex, 256> vertices;
		Shader& shader;
		VAO vao;
		VBO vbo;
		EBO ebo;
		GLuint texture;
	};

	Renderer();
	Renderer(float fov, float aspect);
	~Renderer();
	std::array<Vertex, 4> Quad(float x, float y, float scale);
	void AddBatch(Renderer::Batch batch);
	void Draw();
	void DrawTest();

private:
	Camera cam;
	std::vector<Batch> batches;
};