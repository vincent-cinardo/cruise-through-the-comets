#pragma once
#include <iostream>
#include "Shader.h"

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
	void ProcessInput(float deltaTime);
	void Update(float deltaTime);
	void Render();

private:
	unsigned int width, height;
};

