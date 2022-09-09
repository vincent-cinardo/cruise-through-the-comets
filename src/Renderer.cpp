#include "Renderer.h"

//Evil globals for testing
//Batch batch;
unsigned int vbo, vao, ebo;
Shader shader;
Texture texture;


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
Renderer::Index* Renderer::GenerateIndicesForQuads(int amt)
{
	//DOUBLE CHECK THIS later. Change to array object later on.
	assert(amt > 0);
	Renderer::Index *indices = (Renderer::Index *)malloc(amt);
	for (int i = 0; i < amt; i++)
	{
		int vertex = i * 4;
		indices[i].indices[0] = 0 + vertex;
		indices[i].indices[1] = 1 + vertex;
		indices[i].indices[2] = 2 + vertex;
		indices[i].indices[3] = 2 + vertex;
		indices[i].indices[4] = 3 + vertex;
		indices[i].indices[5] = 0 + vertex;
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

	unsigned int ind[] = {
		0,1,2,2,3,0,
		4,5,6,6,7,4
	};

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(5 * sizeof(float)));

	
	shader.SetMat4("projection", cam.projection);
	shader.SetMat4("view", cam.view);
	shader.SetMat4("model", glm::mat4(1.0f));

	texture = Texture::Texture(".\\textures\\grass.png");
}

void Renderer::Draw()
{

}

//To test first, let's draw two quads
void Renderer::DrawTest()
{
	std::array<Renderer::Vertex, 4> q0 = Quad(-0.5f, -0.5f, 0.0f, 0.5f);
	std::array<Renderer::Vertex, 4> q1 = Quad(0.5f, 0.5f, 1.0f, 0.5f);

	Vertex vertices[8];
	memcpy(vertices, q0.data(), q0.size() * sizeof(Vertex));
	memcpy(vertices + q0.size(), q1.data(), q1.size() * sizeof(Vertex));

	shader.Use();
	glBindVertexArray(vao);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);

}
