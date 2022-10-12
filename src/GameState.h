#pragma once
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
class GameState
{
public:
	virtual ~GameState() = 0;
	virtual void ProcessInput(Game* game, GLFWwindow* window, float deltaTime) = 0;
	virtual void Update(Game* game, GLFWwindow* window, float deltaTime) = 0;
};

