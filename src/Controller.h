#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Controller
{
public:
	static void Init();
	static void ProcessInput(GLFWwindow* window);
private:
	Controller();
	static float inputX, inputY;
};

