#pragma once
#include <iostream>
#include "Renderer.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Texture.h"
#include "Shader.h"
#include "ResourceManager.h"

class BackgroundRenderer : public Renderer
{
public:
	BackgroundRenderer(Shader shader);
	BackgroundRenderer();
	void Render();
};

