#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "Sprite.h"
#include "Texture.h"
#include "Ground.h"
#include "Renderer.h"
#include "stb_image.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

//Camera implementation
#include "Camera.h"

//Matrix/vector math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "main.h"

float lastTime = 0.0f, deltaTime;
float inputX, inputY, inputZ = 0.0f;
unsigned int screenWidth = 1920;
unsigned int screenHeight = 1080;

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
	screenWidth = width;
	screenHeight = height;
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

	Batch batch = Batch::Batch();

	Renderer renderer = Renderer::Renderer(90.0f, (float)screenWidth / (float)screenHeight);
	//renderer.AddBatch(batch);

	renderer.Render();

	while (!glfwWindowShouldClose(window))
	{
		deltaTime = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();
		
		//Input
		processInput(window);

		//Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		renderer.DrawTest(); //Need to get this to work.

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	renderer.~Renderer();
	glfwTerminate();
	return 0;
}