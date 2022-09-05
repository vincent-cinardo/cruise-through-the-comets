#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
class Renderer
{
public:

	struct Vertex
	{
		float position[3];
		float texCoords[2];
		float texture;
	};

	/*struct Vertex //For color, need to rename
	{
		float position[3];
		float color[4];
	};*/

	Renderer();
	Renderer(float fov, float aspect);
	~Renderer();
	Vertex* Quad(float x, float y, float scale, unsigned int textureID);
	void Draw();
	void DrawTest();

private:
	Camera cam;
	glm::mat4 projection;
	glm::mat4 view;
};