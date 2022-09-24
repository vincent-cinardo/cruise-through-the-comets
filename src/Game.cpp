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
	ResourceManager::LoadShader(".\\background.vert", ".\\background.frag", "background");

	ResourceManager::LoadTexture(".\\textures\\stick.png", true, "stick");
	ResourceManager::LoadTexture(".\\textures\\stick1.png", true, "stick1");
	ResourceManager::LoadTexture(".\\textures\\stick2.png", true, "stick2");
	ResourceManager::LoadTexture(".\\textures\\stick3.png", true, "stick3");
	ResourceManager::LoadTexture(".\\textures\\background.jpg", false, "background");
	renderer = new SpriteRenderer(ResourceManager::GetShader("character"));
	backgroundRenderer = new BackgroundRenderer(ResourceManager::GetShader("background"));
	glooper = Glooper::Glooper();
}

void Game::ProcessInput(GLFWwindow* window, float deltaTime)
{
	Controller::ProcessInput(window);
}

void Game::Update(float deltaTime)
{

	glooper.Move(Controller::inputX * 0.01f, Controller::inputY * 0.01f);
}

void Game::Render()
{
	backgroundRenderer->Render();
	renderer->Draw(glooper.GetSprite(), glm::vec3(glooper.GetX(), glooper.GetY(), 0.0f));
}