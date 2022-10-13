#include "Game.h"

Game::Game()
{
	width = 1920u;
	height = 1080u;
	camera = Camera::Camera();
	state = MENU;
}

Game::~Game()
{
	delete glooperRenderer;
	delete backgroundRenderer;
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
	ResourceManager::LoadTexture(".\\textures\\play.png", true, "play");
	ResourceManager::LoadTexture(".\\textures\\retry.png", true, "retry");
	ResourceManager::LoadTexture(".\\textures\\exit.png", true, "exit");
	glooperRenderer = new SpriteRenderer(ResourceManager::GetShader("character"));
	backgroundRenderer = new BackgroundRenderer(ResourceManager::GetShader("background"));
	menuRenderer = new MenuRenderer(ResourceManager::GetShader("UI"));
	glooper = Glooper::Glooper();
	asteroidField = new AsteroidField();
}

void Game::ProcessInput(GLFWwindow* window, float deltaTime)
{
	Controller::ProcessInput(window, deltaTime);
}

void Game::Update(GLFWwindow *window, float deltaTime)
{
	switch (state)
	{
		case PLAY:
		{
			glooper.Move(Controller::inputX * deltaTime * 10.0f, Controller::inputY * deltaTime * 10.0f);
			asteroidField->UpdateAsteroids(deltaTime);
			Collisions();
		}
		break;
		case MENU:
		{
			if (Controller::MouseX >= (camera.GetScreenWidth()/4) && Controller::MouseX <= ((camera.GetScreenWidth()/4) * 3))
			{
				if (Controller::MouseY/camera.GetScreenHeight() >= (215.0f / camera.GetScreenHeight()) && Controller::MouseY / camera.GetScreenHeight() <= (470.0f / camera.GetScreenHeight()))
				{
					//Change texture here
					if (Controller::JustClicked())
					{
						state = PLAY;
					}
				}

				if (Controller::MouseY / camera.GetScreenHeight() >= (540.0f / camera.GetScreenHeight()) && Controller::MouseY / camera.GetScreenHeight() <= (790.0f / camera.GetScreenHeight()))
				{
					if (Controller::JustClicked())
					{
						glfwSetWindowShouldClose(window, true);
					}
				}
			}
		}
		break;
		case LOSE:
		{
			//Need to check in certain spots if cursor is within the MENU's hitbox.
			if (Controller::MouseX >= (camera.GetScreenWidth() / 4) && Controller::MouseX <= ((camera.GetScreenWidth() / 4) * 3))
			{
				if (Controller::MouseY / camera.GetScreenHeight() >= (215.0f / camera.GetScreenHeight()) && Controller::MouseY / camera.GetScreenHeight() <= (470.0f / camera.GetScreenHeight()))
				{
					//Change texture here
					if (Controller::JustClicked())
					{
						delete asteroidField;
						asteroidField = new AsteroidField();
						glooper.SetTexture(ResourceManager::GetTexture("stick"));
						glooper.SetPos(0.0f, 0.0f);
						state = PLAY;
					}
				}

				if (Controller::MouseY / camera.GetScreenHeight() >= (540.0f / camera.GetScreenHeight()) && Controller::MouseY / camera.GetScreenHeight() <= (790.0f / camera.GetScreenHeight()))
				{
					//Change texture here
					if (Controller::JustClicked())
					{
						delete asteroidField;
						glfwSetWindowShouldClose(window, true);
					}
				}
			}
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
			asteroidField->Render(glooperRenderer);
		}
		break;
		case MENU:
		{
			backgroundRenderer->Render();
			menuRenderer->Draw(ResourceManager::GetTexture("play"), glm::vec3(0.0f, 0.3f, 0.0f));
			menuRenderer->Draw(ResourceManager::GetTexture("exit"), glm::vec3(0.0f, -0.3f, 0.0f));
		}
		break;
		case LOSE:
		{
			backgroundRenderer->Render();
			glooperRenderer->Draw(glooper.GetSpriteLose(), glm::vec3(glooper.GetX(), glooper.GetY(), 0.0f));
			asteroidField->Render(glooperRenderer);
			menuRenderer->Draw(ResourceManager::GetTexture("retry"), glm::vec3(0.0f, 0.3f, 0.0f));
			menuRenderer->Draw(ResourceManager::GetTexture("exit"), glm::vec3(0.0f, -0.3f, 0.0f));
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
	for (Asteroid* asteroid : asteroidField->GetAsteroids())
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