#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class SpriteRenderer
{
public:
	SpriteRenderer();
	SpriteRenderer(Shader shader);
	void Init();
	~SpriteRenderer();
	void Draw();
	void Move(float x, float y);
	void Draw(Texture &texture, glm::vec3 position);
	unsigned int GetProgram();

private:
	GLuint vao, vbo, ebo;
	Shader shader, *shaderPtr;
	Texture texture, *texturePtr;
	float x, y;
};

