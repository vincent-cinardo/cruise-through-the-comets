#include "AsteroidField.h"

AsteroidField::AsteroidField()
{
	nextAsteroidSpawn = MathHelper::Random(0.0f, 3.0f);
	lastSpawn = "none";
}

AsteroidField::~AsteroidField()
{
	for (Asteroid* asteroid : asteroids)
	{
		delete asteroid;
		std::cout << "Asteroid deleted in destructor!" << '\n';
	}
}

void AsteroidField::SpawnAsteroid()
{
	Asteroid* asteroid = new Asteroid();
	asteroids.insert(asteroids.begin(), asteroid);
	lastSpawn = asteroids.front()->SpawnedFrom();
	std::cout << "Spawned in an asteroid" << '\n';
}

void AsteroidField::UpdateAsteroids(float dt)
{
	nextAsteroidSpawn -= dt;
	//std::cout << nextAsteroidSpawn << std::endl;
	for (Asteroid *asteroid : asteroids)
	{
		asteroid->Update(dt);
	}
	
	if (!asteroids.empty() && asteroids.back()->ttl <= 0.0f)
	{
		delete asteroids.back();
		asteroids.pop_back();
		std::cout << "Asteroid deleted!" << '\n';
	}

	if (nextAsteroidSpawn <= 0.0f)
	{
		nextAsteroidSpawn = MathHelper::Random(0.0f, 1.0f);
		SpawnAsteroid();
	}
}

void AsteroidField::DeleteAsteroid(Asteroid* asteroid)
{
	delete asteroid;
}

void AsteroidField::Render(Renderer* renderer)
{
	for (Asteroid* asteroid : asteroids)
	{
		renderer->Draw(ResourceManager::GetTexture("asteroid"), glm::vec3(asteroid->GetX(), asteroid->GetY(), 0.0f), asteroid->GetSpriteAngle());
	}
}

std::vector<Asteroid*> AsteroidField::GetAsteroids()
{
	return asteroids;
}

bool AsteroidField::Empty()
{
	if (asteroids.empty())
	{
		return true;
	}
	else
	{
		return false;
	}	
}