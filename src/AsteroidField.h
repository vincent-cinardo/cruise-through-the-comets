#pragma once
#include <iostream>
#include "Asteroid.h"

class AsteroidField
{
public:
	AsteroidField();
	void SpawnAsteroid();
private:
	std::vector<Asteroid> astroids;
};

