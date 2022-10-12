#pragma once
#include <iostream>
#include "Shader.h"
#include "ResourceManager.h";
#include "Camera.h"
#include "Glooper.h"
#include "Controller.h"
#include "Renderer.h"
#include "BackgroundRenderer.h"
#include "SpriteRenderer.h"
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
	bool CheckCollision(Glooper glooper, Asteroid *asteroid);


private:

	unsigned int width, height;
	Glooper glooper;
	AsteroidField asteroidField;
	Renderer *glooperRenderer, *backgroundRenderer;
};


