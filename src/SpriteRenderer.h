#pragma once
#include "Renderer.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class SpriteRenderer : public Renderer
{
public:
	SpriteRenderer();
	SpriteRenderer(Shader shader);
	void Init();
	~SpriteRenderer();
	void Draw();
	void Move(float x, float y);
	void Render();
	//void Draw(Texture &texture, glm::vec3 position);
	//void Draw(Texture& texture, glm::vec3 position, float angle);
	//void Draw(Texture& texture, glm::vec3 position, glm::vec2 bottomleft);
	unsigned int GetProgram();

private:
	float x, y;
};

