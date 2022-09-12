#include "Game.h"

Game::Game()
{
	width = 1920u;
	height = 1080u;
}

Game::~Game()
{
	
}

void Game::Init()
{
	ResourceManager::LoadShader(".\\default.vert", ".\\default.frag", "default");
	ResourceManager::LoadTexture(".\\textures\\grass.png", false, "grass");
}

void Game::ProcessInput(float deltaTime)
{

}

void Game::Update(float deltaTime)
{

}

void Game::Render()
{

}