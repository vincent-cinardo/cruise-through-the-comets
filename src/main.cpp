#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "Sprite.h"
#include "Texture.h"
#include "stb_image.h"

//Camera
#include "Camera.h"

//Matrix/vector math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "main.h"

float lastTime = 0.0f, deltaTime;
float inputX, inputY, inputZ = 0.0f;

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

	GLFWwindow* window = glfwCreateWindow(800, 600, "Alien Game", NULL, NULL);
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

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, frame_buffer_callback);
	glfwSetScrollCallback(window, scroll_call_back);

	stbi_set_flip_vertically_on_load(true);

	Sprite sprite = Sprite::Sprite();
	Sprite* spritePtr = &sprite;

	Camera cam = Camera::Camera();
	Camera* camPtr = &cam;

	//glm::mat4 view = glm::mat4(1.0f);
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));

	//glm::mat4 projection = glm::ortho(-15, 15,,,,);

	while (!glfwWindowShouldClose(window))
	{
		deltaTime = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();
		
		//Input
		processInput(window);


		//Game Data Manipulation
		//Implement Z movement by scrolling.
		spritePtr->Move(10.0f * deltaTime * inputX, 10.0f * deltaTime * inputY);

		//Change to this to make the camera move with sprite
		//camPtr->Move(10.0f * deltaTime * inputX, 10.0f * deltaTime * inputY, 0.0f);

		camPtr->ZoomOrtho(30.0f, 30.0f, spritePtr->GetProgram());
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