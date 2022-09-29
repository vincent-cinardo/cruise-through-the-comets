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
	ResourceManager::LoadShader(".\\asteroid.vert", ".\\asteroid.frag", "asteroid");
	ResourceManager::shaders["asteroid"].SetMat4("projection", camera.projection);
	ResourceManager::shaders["asteroid"].SetMat4("view", camera.view);

	ResourceManager::LoadTexture(".\\textures\\asteroid.png", false, "asteroid");
	ResourceManager::LoadTexture(".\\textures\\stick.png", true, "stick");
	ResourceManager::LoadTexture(".\\textures\\stick1.png", true, "stick1");
	ResourceManager::LoadTexture(".\\textures\\stick2.png", true, "stick2");
	ResourceManager::LoadTexture(".\\textures\\stick3.png", true, "stick3");
	ResourceManager::LoadTexture(".\\textures\\background.jpg", false, "background");
	renderer = new SpriteRenderer(ResourceManager::GetShader("character"));
	backgroundRenderer = BackgroundRenderer::BackgroundRenderer(ResourceManager::GetShader("background"));
	glooper = Glooper::Glooper();
	asteroidField = AsteroidField::AsteroidField();
}

void Game::ProcessInput(GLFWwindow* window, float deltaTime)
{
	Controller::ProcessInput(window);
}

void Game::Update(float deltaTime)
{
	glooper.Move(Controller::inputX * deltaTime * 10.0f, Controller::inputY * deltaTime * 10.0f);
	asteroidField.UpdateAsteroids(deltaTime);
	Collisions();
}

void Game::Render()
{
	backgroundRenderer.Render();
	renderer->Draw(glooper.GetSprite(), glm::vec3(glooper.GetX(), glooper.GetY(), 0.0f));
	asteroidField.Render(renderer);
}

void Game::Collisions()
{
	bool collision = false;
	for (Asteroid* asteroid : asteroidField.GetAsteroids())
	{
		collision = CheckCollision(glooper, asteroid);
		if (collision)
		{
			state = Lose;
			std::cout << "asteroid hit!" << std::endl;
		}
		collision = false;
	}
}

bool Game::CheckCollision(Glooper glooper, Asteroid *asteroid)
{
	bool x = glooper.GetX() + glooper.GetSize() >= asteroid->GetX() && asteroid->GetX() + asteroid->GetSize() >= glooper.GetX();
	bool y = glooper.GetY() + glooper.GetSize() >= asteroid->GetY() && asteroid->GetY() + asteroid->GetSize() >= glooper.GetY();
	return x && y;
}