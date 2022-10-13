#pragma once
#include "Renderer.h"

class MenuRenderer: public Renderer
{
public:
	MenuRenderer();
	MenuRenderer(Shader shader);
	~MenuRenderer();
	void SetMenu(const char* menuName);
	void SetLocation(float x, float y, float height, float width);
	void Draw(Texture &texture, glm::vec3 pos, glm::vec2 dim);
private:
	float width, height;
};

