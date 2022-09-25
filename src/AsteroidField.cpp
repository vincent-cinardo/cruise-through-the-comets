#include "AsteroidField.h"

AsteroidField::AsteroidField()
{
	
}

void AsteroidField::SpawnAsteroid()
{
	Asteroid *asteroid = new Asteroid();
	asteroids.push_back(asteroid);
}

void AsteroidField::UpdateAsteroids(float dt)
{
	for (Asteroid *asteroid : asteroids)
	{
		asteroid->Update(dt);
	}
}