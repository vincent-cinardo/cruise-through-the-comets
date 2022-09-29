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
		std::cout << "Asteroid deleted in destructor!" << std::endl;
	}
}

void AsteroidField::SpawnAsteroid()
{
	Asteroid* asteroid = new Asteroid();
	asteroids.insert(asteroids.begin(), asteroid);
	lastSpawn = asteroids.front()->SpawnedFrom();
	std::cout << "Spawned in an asteroid" << std::endl;
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
		std::cout << "Asteroid deleted!" << std::endl;
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

void AsteroidField::Render(SpriteRenderer* renderer)
{
	for (Asteroid* asteroid : asteroids)
	{
		renderer->Draw(ResourceManager::GetTexture("asteroid"), glm::vec3(asteroid->GetX(), asteroid->GetY(), 0.0f), asteroid->GetSpriteAngle());
	}
}
