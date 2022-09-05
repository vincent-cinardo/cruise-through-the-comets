#include "Renderer.h"

Renderer::Renderer() 
{
	std::cout << "sizeof(Vertex) == " << sizeof(Vertex) << std::endl;
}

Renderer::~Renderer()
{

}

Renderer::Renderer(float fov, float aspect)
{
	std::cout << "sizeof(Vertex) == " << sizeof(Vertex) << std::endl;

	view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
	projection = glm::perspective(fov, aspect, -1.0f, -10.0f);
	cam = Camera::Camera(view, projection);
}

//Create vertex data for a quad on a 2D plane with a texture.
Renderer::Vertex* Renderer::Quad(float x, float y, float scale, unsigned int textureID)
{
	//Bottom left
	Vertex v0{
		{x, y, 0.0f},
		{0.0f, 0.0f},
		textureID
	};

	//Bottom right
	Vertex v1{
		{x + scale, y, 0.0f},
		{1.0f, 0.0f},
		textureID
	};

	//Top right
	Vertex v2{
		{x + scale, y + scale, 0.0f},
		{1.0f, 1.0f},
		textureID
	};

	//Top left
	Vertex v3{
		{x, y + scale, 0.0f},
		{0.0f, 1.0f},
		textureID
	};

	Vertex arr[4] = {v0, v1, v2, v3};

	return arr;
}

void Renderer::Draw()
{
	
}

//To test first, let's draw two quads
void Renderer::DrawTest()
{
	Vertex vertices[4];
	Vertex *q0 = Quad(1.0f, 1.0f, 1.0f, 0.0f);
	memcpy(vertices, q0, 4 * sizeof(Vertex));

	//memcpy(,,);
}

