#include "Controller.h"

float Controller::inputX = 0.0f;
float Controller::inputY = 0.0f;
float Controller::MouseX = 0.0f;
float Controller::MouseY = 0.0f;

void Controller::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	MouseX = (float) xpos;
	MouseY = (float) ypos;
}

void Controller::Init(GLFWwindow *window)
{
	glfwSetCursorPosCallback(window, cursor_position_callback);
}

void Controller::ProcessInput(GLFWwindow* window)
{
	Controller::inputX = 0.0f;
	Controller::inputY = 0.0f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		inputY += 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		inputY += -1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		inputX += -1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		inputX += 1.0f;
	}
}