#include "Renderer.h"

Renderer::Renderer() 
{
	std::cout << "sizeof(Vertex) == " << sizeof(Vertex) << std::endl;
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
	glm::mat4 projection = glm::perspective(90.0f, (float) 1920/ (float)1080, -1.0f, -10.0f);
	cam = Camera::Camera(view, projection);

	//Need to make edits, use camera for retrieving view and projection. ADD PROJECTION TO CAMERA CLASS
}

Renderer::~Renderer()
{
	for (Batch batch : batches)
	{
		batch.~Batch();
	}
}

Renderer::Renderer(float fov, float aspect)
{
	std::cout << "sizeof(Vertex) == " << sizeof(Vertex) << std::endl;

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
	glm ::mat4 projection = glm::perspective(fov, aspect, -1.0f, -10.0f);
	cam = Camera::Camera(view, projection);
}



//Create vertex data for a quad on a 2D plane with a texture.
std::array<Renderer::Vertex, 4> Renderer::Quad(float x, float y, float scale)
{
	//Bottom left
	Vertex v0{
		{x, y, 0.0f},
		{0.0f, 0.0f},
		//textureID
	};

	//Bottom right
	Vertex v1{
		{x + scale, y, 0.0f},
		{1.0f, 0.0f},
		//textureID
	};

	//Top right
	Vertex v2{
		{x + scale, y + scale, 0.0f},
		{1.0f, 1.0f},
		//textureID
	};

	//Top left
	Vertex v3{
		{x, y + scale, 0.0f},
		{0.0f, 1.0f},
		//textureID
	};

	std::array<Renderer::Vertex, 4> arr = {v0,v1,v2,v3};

	return arr;
}

void Renderer::AddBatch(Batch batch)
{
	batches.push_back(batch);
}

void Renderer::Draw()
{
	/*while (!batches.empty())
	{
		Renderer::Batch batch = batches.back();

		batch.vao 

		batch.vertices;
	}*/

}

/* Delete this when done
	struct Batch
	{
		std::array<Vertex, 256> vertices;
		Shader& shader;
		VAO vao;
		VBO vbo;
		EBO ebo;
		GLuint texture;
	};*/

//To test first, let's draw two quads
void Renderer::DrawTest()
{
	for (Batch batch : batches)
	{
		batch.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(batch.ebo.GetCount()), GL_UNSIGNED_INT, 0);
	}
}
