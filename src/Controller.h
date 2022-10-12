#pragma once
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Controller
{
public:
	static void ProcessInput(GLFWwindow* window);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void Init(GLFWwindow* window);
	static float inputX;
	static float inputY;
	static float MouseX;
	static float MouseY;
private:
	Controller();
};

