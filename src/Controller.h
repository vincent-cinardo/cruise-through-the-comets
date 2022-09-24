#pragma once
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Controller
{
public:
	static void Init();
	static void ProcessInput(GLFWwindow* window);
	static float inputX;
	static float inputY;
private:
	Controller();
};

