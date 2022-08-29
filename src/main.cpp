#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "Sprite.h"
#include "Texture.h"
#include "stb_image.h"

//Camera implementation
#include "Camera.h"

//Matrix/vector math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "main.h"

float lastTime = 0.0f, deltaTime;
float inputX, inputY, inputZ = 0.0f;
const unsigned int screenWidth = 1920;
const unsigned int screenHeight = 1080;

void scroll_call_back(GLFWwindow* window, double xoffset, double yoffset)
{
	inputZ = yoffset;
}

void processInput(GLFWwindow* window)
{
	inputX = 0.0f;
	inputY = 0.0f;
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

void frame_buffer_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(int argc, int* argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(screenHeight, screenHeight, "Alien Game", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Window failed to open" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, screenWidth, screenHeight);

	glfwSetFramebufferSizeCallback(window, frame_buffer_callback);
	glfwSetScrollCallback(window, scroll_call_back);

	stbi_set_flip_vertically_on_load(true);

	Sprite sprite = Sprite::Sprite();
	Sprite* spritePtr = &sprite;

	//Sprite sweetMike = Sprite::Sprite(2.0f, 2.0f, ".\\textures\\dog.png");

	Camera cam = Camera::Camera();
	Camera* camPtr = &cam;

	while (!glfwWindowShouldClose(window))
	{
		deltaTime = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();
		
		//Input
		processInput(window);

		//Game Data Manipulation
		//Implement Z movement by scrolling.
		spritePtr->Move(10.0f * deltaTime * inputX, 10.0f * deltaTime * inputY);

		//Uncomment this to make the camera move with sprite
		//camPtr->Move(10.0f * deltaTime * inputX, 10.0f * deltaTime * inputY, 0.0f);

		std::cout << inputZ << std::endl;
		camPtr->ZoomOrtho(10.0f * inputZ * deltaTime, screenWidth/screenHeight, spritePtr->GetProgram());
		inputZ = 0;
		camPtr->View(0.0f, 0.0f, spritePtr->GetProgram());

		//Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		spritePtr->Draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	spritePtr->~Sprite();
	glfwTerminate();
	return 0;
}