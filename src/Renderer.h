#pragma once
#include "texture.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer
{
public:
	Renderer();
	Renderer(Shader* shader);
	virtual void Render() = 0;
	void Draw(Texture& texture, glm::vec3 position);
	void Draw(Texture& texture, glm::vec3 position, float angle);

protected:
	Shader shader;
	Texture texture;
	GLuint vao, vbo;
};