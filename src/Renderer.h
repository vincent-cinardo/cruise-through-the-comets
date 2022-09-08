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
#include "Texture.h"
#include "Camera.h"
#include "Shader.h"
#include "Batch.h"
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

	Renderer();
	Renderer(float fov, float aspect);
	~Renderer();
	std::array<Vertex, 4> Quad(float x, float y, float scale);
	void AddBatch(Batch batch);
	void Draw();
	void DrawTest();

private:
	Camera cam;
	std::vector<Batch> batches;
};