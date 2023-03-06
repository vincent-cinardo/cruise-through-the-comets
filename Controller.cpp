#include "Controller.h"

float Controller::inputX = 0.0f;
float Controller::inputY = 0.0f;
float Controller::MouseX = 0.0f;
float Controller::MouseY = 0.0f;
bool Controller::HoldingM1 = false;
float Controller::HoldM1Time = 0.0f;

void Controller::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		HoldingM1 = true;
	}
	else HoldingM1 = false;
}

void Controller::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	MouseX = (float) xpos;
	MouseY = (float) ypos;
}

void Controller::Init(GLFWwindow *window)
{
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
}

void Controller::ProcessInput(GLFWwindow* window, float dt)
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

	if (HoldingM1)
	{
		HoldM1Time += dt;
	}
	else
	{
		HoldM1Time = 0.0f;
	}
}

bool Controller::JustClicked()
{
	if (HoldM1Time <= 0.4f && HoldingM1)
	{
		return true;
	}
	else return false;
}