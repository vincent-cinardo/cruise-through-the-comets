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
	delete spaceshipRenderer;
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
	ResourceManager::LoadTexture(".\\textures\\background.jpg", false, "background");
	ResourceManager::LoadTexture(".\\textures\\asteroid.png", true, "asteroid");
	ResourceManager::LoadTexture(".\\textures\\spaceship.png", true, "spaceship");
	ResourceManager::LoadTexture(".\\textures\\spaceship1.png", true, "spaceship1");
	ResourceManager::LoadTexture(".\\textures\\spaceship2.png", true, "spaceship2");
	ResourceManager::LoadTexture(".\\textures\\spaceship3.png", true, "spaceship3");
	ResourceManager::LoadTexture(".\\textures\\play.png", true, "play");
	ResourceManager::LoadTexture(".\\textures\\retry.png", true, "retry");
	ResourceManager::LoadTexture(".\\textures\\exit.png", true, "exit");
	backgroundRenderer = new BackgroundRenderer(ResourceManager::GetShader("background"));
	spaceshipRenderer = new SpriteRenderer(ResourceManager::GetShader("character"));
	menuRenderer = new MenuRenderer(ResourceManager::GetShader("UI"));
	spaceship = Spaceship::Spaceship();
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
			spaceship.Move(Controller::inputX * deltaTime * 10.0f, Controller::inputY * deltaTime * 10.0f);
			asteroidField->UpdateAsteroids(deltaTime);
			Collisions();
		}
		break;
		case MENU:
		{
			bool mouseIsMiddle = Controller::MouseX >= (camera.GetScreenWidth() / 4) && Controller::MouseX <= ((camera.GetScreenWidth() / 4) * 3);
			bool mouseIsTopButton = Controller::MouseY / camera.GetScreenHeight() >= (215.0f / camera.GetScreenHeight())
				&& Controller::MouseY / camera.GetScreenHeight() <= (470.0f / camera.GetScreenHeight());
			bool mouseIsBottomButton = Controller::MouseY / camera.GetScreenHeight() >= (540.0f / camera.GetScreenHeight())
				&& Controller::MouseY / camera.GetScreenHeight() <= (790.0f / camera.GetScreenHeight());
			if (mouseIsMiddle)
			{
				if (mouseIsTopButton)
				{
					//Change texture here
					if (Controller::JustClicked())
					{
						state = PLAY;
					}
				}

				if (mouseIsBottomButton)
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
			bool mouseIsMiddle = Controller::MouseX >= (camera.GetScreenWidth() / 4) && Controller::MouseX <= ((camera.GetScreenWidth() / 4) * 3);
			bool mouseIsTopButton = Controller::MouseY / camera.GetScreenHeight() >= (215.0f / camera.GetScreenHeight())
				&& Controller::MouseY / camera.GetScreenHeight() <= (470.0f / camera.GetScreenHeight());
			bool mouseIsBottomButton = Controller::MouseY / camera.GetScreenHeight() >= (540.0f / camera.GetScreenHeight())
				&& Controller::MouseY / camera.GetScreenHeight() <= (790.0f / camera.GetScreenHeight());
			if (mouseIsMiddle)
			{
				if (mouseIsTopButton)
				{
					if (Controller::JustClicked())
					{
						delete asteroidField;
						asteroidField = new AsteroidField();
						spaceship.SetTexture(ResourceManager::GetTexture("spaceship"));
						spaceship.SetPos(0.0f, 0.0f);
						state = PLAY;
					}
				}

				if (mouseIsBottomButton)
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
	}
}

void Game::Render()
{
	switch (state)
	{
		case PLAY:
		{
			backgroundRenderer->Render();
			spaceshipRenderer->Draw(spaceship.GetSprite(), glm::vec3(spaceship.GetX(), spaceship.GetY(), 0.0f));
			asteroidField->Render(spaceshipRenderer);
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
			spaceshipRenderer->Draw(spaceship.GetSpriteLose(), glm::vec3(spaceship.GetX(), spaceship.GetY(), 0.0f));
			asteroidField->Render(spaceshipRenderer);
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
		collision = CheckCollision(spaceship, asteroid);
		if (collision)
		{
			state = LOSE;
			std::cout << "Asteroid hit!" << '\n';
		}
		collision = false;
	}
}

bool Game::CheckCollision(Spaceship spaceship, Asteroid *asteroid)
{
	bool x = spaceship.GetX() + spaceship.GetSize() >= asteroid->GetX() && asteroid->GetX() + asteroid->GetSize() >= spaceship.GetX();
	bool y = spaceship.GetY() + spaceship.GetSize() >= asteroid->GetY() && asteroid->GetY() + asteroid->GetSize() >= spaceship.GetY();
	return x && y;
}