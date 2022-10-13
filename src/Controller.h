#pragma once
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Controller
{
public:
	static void ProcessInput(GLFWwindow* window, float dt);
	static bool JustClicked();
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void Init(GLFWwindow* window);
	static float inputX;
	static float inputY;
	static float MouseX;
	static float MouseY;
	static bool HoldingM1;
	static float HoldM1Time;
private:
	Controller();
};

