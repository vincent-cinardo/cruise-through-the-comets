#pragma once
#include <iostream>
#include "Shader.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Camera.h"
#include "Glooper.h"
#include "Controller.h"
#include "BackgroundRenderer.h"
#include "AsteroidField.h"

enum GameState {
	Active,
	Menu,
	Win,
	Lose
};

class Game
{
public:
	GameState state;
	Game();
	~Game();
	void Init();
	void ProcessInput(GLFWwindow *window, float deltaTime);
	void Update(float deltaTime);
	void Render();
	void Collisions();
	bool CheckCollision(Glooper glooper, Asteroid *asteroid);
	Camera camera;

private:
	unsigned int width, height;
	Glooper glooper;
	AsteroidField asteroidField;
	SpriteRenderer *renderer;
	BackgroundRenderer backgroundRenderer;
};

