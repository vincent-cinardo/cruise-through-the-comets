#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Game.h"
#include "Shader.h"
#include "Texture.h"
#include "Ground.h"
#include "stb_image.h"

//Camera implementation
#include "Camera.h"

//Matrix/vector math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "main.h"

Game *game;

float lastTime = 0.0f, deltaTime;
float inputX, inputY, inputZ = 0.0f;
unsigned int screenWidth = 1920;
unsigned int screenHeight = 1080;

void scroll_call_back(GLFWwindow* window, double xoffset, double yoffset)
{
	inputZ = yoffset;
}

void frame_buffer_callback(GLFWwindow* window, int width, int height)
{
	screenWidth = width;
	screenHeight = height;
	glViewport(0, 0, width, height);
	game->camera.Aspect((float) width, (float) height);
}

int main(int argc, int* argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(screenHeight, screenHeight, "Alien Game", NULL, NULL);
	glfwSetWindowSize(window, screenWidth, screenHeight);
	glfwSetWindowPos(window, 0, 0);

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

	//THESE WILL NOW BE SET IN THE CONTROLLER CLASS DELETE WHEN DONE
	glfwSetFramebufferSizeCallback(window, frame_buffer_callback);
	//glfwSetScrollCallback(window, scroll_call_back);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	stbi_set_flip_vertically_on_load(true);

	Game theGame = Game::Game();
	game = &theGame;

	game->Init();

	while (!glfwWindowShouldClose(window))
	{
		deltaTime = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();
		
		//Input
		//processInput(window);
		game->ProcessInput(window, deltaTime);

		//Update
		game->Update(deltaTime);

		//May delete this, review after cleanup.
		if (game->state == GameState::Lose)
		{
			glfwSetWindowShouldClose(window, true);
		}

		//Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		game->Render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ResourceManager::Clear();
	glfwTerminate();
	return 0;
}