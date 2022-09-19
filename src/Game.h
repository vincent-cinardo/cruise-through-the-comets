#pragma once
#include <iostream>
#include "Shader.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Camera.h"
#include "Glooper.h"
#include "Controller.h"

enum GameState {
	Active,
	Menu,
	Win,
	Lose
};

class Game
{
public:
	Game();
	~Game();
	void Init();
	void ProcessInput(GLFWwindow *window, float deltaTime);
	void Update(float deltaTime);
	void Render();
	Camera camera;

private:
	unsigned int width, height;
	Glooper glooper;
	SpriteRenderer *renderer;
};

