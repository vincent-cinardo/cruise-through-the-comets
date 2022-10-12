#include "Game.h"

Game::Game()
{
	width = 1920u;
	height = 1080u;
	camera = Camera::Camera();
	state = PLAY;
}

Game::~Game()
{
	//delete glooperRenderer;
	//delete backgroundRenderer;
}

void Game::Init()
{
	std::cout << "Loading shaders..." << std::endl;
	ResourceManager::LoadShader(".\\default.vert", ".\\default.frag", "default");
	ResourceManager::shaders["default"].Use();
	ResourceManager::shaders["default"].SetMat4("projection", camera.projection);
	ResourceManager::shaders["default"].SetMat4("view", camera.view);
	ResourceManager::LoadShader(".\\character.vert", ".\\character.frag", "character");
	ResourceManager::shaders["character"].Use();
	ResourceManager::shaders["character"].SetMat4("projection", camera.projection);
	ResourceManager::shaders["character"].SetMat4("view", camera.view);
	ResourceManager::LoadShader(".\\background.vert", ".\\background.frag", "background");
	ResourceManager::LoadShader(".\\asteroid.vert", ".\\asteroid.frag", "asteroid");
	ResourceManager::shaders["asteroid"].SetMat4("projection", camera.projection);
	ResourceManager::shaders["asteroid"].SetMat4("view", camera.view);
	ResourceManager::LoadShader(".\\UI.vert", ".\\UI.frag", "UI");

	std::cout << "Loading textures..." << std::endl;
	ResourceManager::LoadTexture(".\\textures\\asteroid.png", true, "asteroid");
	ResourceManager::LoadTexture(".\\textures\\stick.png", true, "stick");
	ResourceManager::LoadTexture(".\\textures\\stick1.png", true, "stick1");
	ResourceManager::LoadTexture(".\\textures\\stick2.png", true, "stick2");
	ResourceManager::LoadTexture(".\\textures\\stick3.png", true, "stick3");
	ResourceManager::LoadTexture(".\\textures\\background.jpg", false, "background");
	ResourceManager::LoadTexture(".\\textures\\losescreen.jpg", false, "losescreen");
	//ResourceManager::LoadTexture(".\\textures\\retry.jpg", false, "background");
	//ResourceManager::LoadTexture(".\\textures\\play.jpg", false, "background");
	//ResourceManager::LoadTexture(".\\textures\\menu.jpg", false, "background");
	glooperRenderer = new SpriteRenderer(ResourceManager::GetShader("character"));
	backgroundRenderer = new BackgroundRenderer(ResourceManager::GetShader("background"));
	glooper = Glooper::Glooper();
	asteroidField = AsteroidField::AsteroidField();
}

void Game::ProcessInput(GLFWwindow* window, float deltaTime)
{
	Controller::ProcessInput(window);
}

void Game::Update(GLFWwindow *window, float deltaTime)
{
	switch (state)
	{
		case PLAY:
		{
			glooper.Move(Controller::inputX * deltaTime * 10.0f, Controller::inputY * deltaTime * 10.0f);
			asteroidField.UpdateAsteroids(deltaTime);
			Collisions();
		}
		break;
		case MENU:
		{

		}
		break;
		case LOSE:
		{
			/*std::ofstream stream;
			stream.open("score.txt", std::ios_base::app);
			if (stream)
			{
				stream << std::to_string(glfwGetTime()) + '\n';
				stream.close();
			}
			*/
			
			//glfwSetWindowShouldClose(window, true);
		}
		break;
		case SCORE:
		{

		}
		break;	
	}
}

void Game::Render()
{
	switch (state)
	{
		case PLAY:
		{
			backgroundRenderer->Render();
			glooperRenderer->Draw(glooper.GetSprite(), glm::vec3(glooper.GetX(), glooper.GetY(), 0.0f));
			asteroidField.Render(glooperRenderer);
		}
		break;
		case MENU:
		{
			backgroundRenderer->Render();
		}
		break;
		case LOSE:
		{
			backgroundRenderer->Render();
			glooperRenderer->Draw(glooper.GetSpriteLose(), glm::vec3(glooper.GetX(), glooper.GetY(), 0.0f));
			asteroidField.Render(glooperRenderer);
			//Need to create a display window here
		}
		break;
		case SCORE:
		{
			backgroundRenderer->Render();
		}
		break;
	}
}

void Game::Collisions()
{
	bool collision = false;
	for (Asteroid* asteroid : asteroidField.GetAsteroids())
	{
		collision = CheckCollision(glooper, asteroid);
		if (collision)
		{
			state = LOSE;
			std::cout << "Asteroid hit!" << std::endl;
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