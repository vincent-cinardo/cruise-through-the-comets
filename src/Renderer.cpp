#include "Renderer.h"

Renderer::Renderer() 
{
	std::cout << "sizeof(Vertex) == " << sizeof(Vertex) << std::endl;
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
	glm::mat4 projection = glm::perspective(90.0f, (float) 1920/ (float)1080, 1.0f, -12.0f);
	cam = Camera::Camera(view, projection);
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
	glm ::mat4 projection = glm::perspective(fov, aspect, 1.0f, -12.0f);
	cam = Camera::Camera(view, projection);
}

//Create vertex data for a quad on a 2D plane with a texture.
std::array<Renderer::Vertex, 4> Renderer::Quad(float x, float y, float texture, float scale)
{
	//Bottom left
	Vertex v0{
		{x, y, 0.0f},
		{0.0f, 0.0f},
		texture
	};

	//Bottom right
	Vertex v1{
		{x + scale, y, 0.0f},
		{1.0f, 0.0f},
		texture
	};

	//Top right
	Vertex v2{
		{x + scale, y + scale, 0.0f},
		{1.0f, 1.0f},
		texture
	};

	//Top left
	Vertex v3{
		{x, y + scale, 0.0f},
		{0.0f, 1.0f},
		texture
	};

	//std::cout << "v0 " << v0.position[0] << " " << v0.position[1] << " " << v0.position[2] << std::endl;

	return { v0,v1,v2,v3 };
}

//Generate an indices array for an ammount of quads. Pairs with the quad function.
std::vector<Renderer::Index> Renderer::GenerateIndicesForQuads(int amt)
{
	//DOUBLE CHECK THIS later. Change to array object later on.
	assert(amt > 0);
	std::vector<Renderer::Index> indices;
	for (int i = 0; i < amt; i++)
	{
		unsigned int vertex = i * 4;
		Renderer::Index index
		{
			0u + vertex,
			1u + vertex,
			2u + vertex,
			2u + vertex,
			3u + vertex,
			0u + vertex
		};
		indices.push_back(index);
	}
	return indices;
}

void Renderer::AddBatch(Batch batch)
{
	batches.push_back(batch);
}

void Renderer::Render()
{
	shader = Shader::Shader(".\\default.vert", ".\\default.frag");
	shader.Use();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 1000, nullptr, GL_DYNAMIC_DRAW);

	std::vector<Renderer::Index> ind = GenerateIndicesForQuads(24);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 24 * sizeof(unsigned int), ind.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	shader.SetMat4("projection", cam.projection);
	shader.SetMat4("view", cam.view);
	shader.SetMat4("model", glm::mat4(1.0f));

	texture = Texture::Texture(".\\textures\\grass.png", false);
}

void Renderer::Draw()
{

}

//To test first, let's draw two quads
void Renderer::DrawTest()
{
	std::array<Renderer::Vertex, 4> q0 = Quad(0.0f, 0.0f, 0.0f, 1.0f);
	std::array<Renderer::Vertex, 4> q1 = Quad(0.0f, 1.0f, 1.0f, 1.0f);
	std::array<Renderer::Vertex, 4> q2 = Quad(1.0f, 0.0f, 0.0f, 1.0f);
	std::array<Renderer::Vertex, 4> q3 = Quad(1.0f, 1.0f, 0.0f, 1.0f);

	Vertex vertices[16];
	memcpy(vertices, q0.data(), 4 * sizeof(Vertex));
	memcpy(vertices + 4, q1.data(), 4 * sizeof(Vertex));
	memcpy(vertices + 8, q2.data(), 4 * sizeof(Vertex));
	memcpy(vertices + 12, q3.data(), 4 * sizeof(Vertex));

	shader.Use();
	glBindVertexArray(vao);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glDrawElements(GL_TRIANGLES, 32, GL_UNSIGNED_INT, nullptr);
}
