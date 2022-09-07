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

void Renderer::AddBatch(Renderer::Batch batch)
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

	std::array<Renderer::Vertex, 4> q0 = Quad(0.0f, 0.0f, 0.5f);
	std::array<Renderer::Vertex, 4> q1 = Quad(0.0f, 0.0f, 0.5f);

	float* vertices = new float[q0.size() + q1.size()];

	/// <summary>
	/// Last left off here. This data needs to go into the vertex buffer object. The draw call is not working
	/// </summary>

	memcpy(vertices, q0.data(), q0.size() * sizeof(float));
	memcpy(vertices + 4, q1.data(), q1.size() * sizeof(float));

	//Imagine this batch inside the class array
	Shader shader = Shader::Shader(".\\ground.vert", ".\\ground.frag");
	Renderer::Batch batch{
		{},
		shader,
		VAO::VAO(),
		VBO::VBO(vertices, 1),
		EBO::EBO({}, 1),
		0
	};

	
	batch.vao.Bind();
	batch.vbo.Bind();
	batch.ebo.Bind();

	batch.vao.SetAttribute(0, q0.size() * sizeof(float), 0);
	batch.vao.SetAttribute(1, q1.size() * sizeof(float), 3 * sizeof(float));

	batch.shader.Use();

	glDrawArrays(GL_TRIANGLES, 0, 24); 

	//memcpy(,,);
}

