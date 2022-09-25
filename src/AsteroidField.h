#pragma once
#include <iostream>
#include <vector>
#include "Asteroid.h"

class AsteroidField
{
public:
	AsteroidField();
	void SpawnAsteroid();
	void UpdateAsteroids(float dt);
private:
	std::vector<Asteroid *> asteroids;
};

