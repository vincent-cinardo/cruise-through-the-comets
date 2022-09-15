#include "Game.h"

Game::Game()
{
	width = 1920u;
	height = 1080u;
	camera = Camera::Camera();
}

Game::~Game()
{
	
}

void Game::Init()
{
	ResourceManager::LoadShader(".\\default.vert", ".\\default.frag", "default");
	ResourceManager::shaders["default"].Use();
	ResourceManager::shaders["default"].SetMat4("projection", camera.projection);
	ResourceManager::shaders["default"].SetMat4("view", camera.view);
	ResourceManager::LoadShader(".\\ground.vert", ".\\ground.frag", "ground");
	ResourceManager::LoadShader(".\\character.vert", ".\\character.frag", "character");
	ResourceManager::shaders["character"].Use();
	ResourceManager::shaders["character"].SetMat4("projection", camera.projection);
	ResourceManager::shaders["character"].SetMat4("view", camera.view);
	//ResourceManager::shaders["character"].SetMat4("view", camera.view);
	/// Will need to set ground uniforms

	ResourceManager::LoadTexture(".\\textures\\stick.png", true, "stick");
	
	renderer = new SpriteRenderer(ResourceManager::GetShader("character"));
	//ResourceManager::GetShader("default").Use();
}

void Game::ProcessInput(float deltaTime)
{

}

void Game::Update(float deltaTime)
{

}

void Game::Render()
{
	renderer->Draw(ResourceManager::GetTexture("stick"), glm::vec3(-2.0f, 0.0f, 0.0f));
}