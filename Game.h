#pragma once
#include <iostream>
#include "Shader.h"
#include "ResourceManager.h";
#include "Camera.h"
#include "Spaceship.h"
#include "Controller.h"
#include "Renderer.h"
#include "BackgroundRenderer.h"
#include "SpriteRenderer.h"
#include "MenuRenderer.h"
#include "AsteroidField.h"

class Game
{
	enum GameState{
		MENU,
		PLAY,
		LOSE,
		SCORE
	};

public:
	GameState state;
	Camera camera;
	Game();
	~Game();
	void Init();
	void ProcessInput(GLFWwindow *window, float deltaTime);
	void Update(GLFWwindow* window, float deltaTime);
	void Render();
	void Collisions();
	bool CheckCollision(Spaceship spaceship, Asteroid *asteroid);


private:

	unsigned int width, height;
	Spaceship spaceship;
	AsteroidField* asteroidField;
	Renderer *spaceshipRenderer, *backgroundRenderer, *menuRenderer;
};


