#pragma once
#include <cstdlib>
#include <ctime>
#include "AsteroidField.h"

class Asteroid
{
public:
	Asteroid(); 
	Asteroid(AsteroidField* asteroidField);
	void Update(float dt);
	void Move(float dt);
	void Hit();
	void SpawnNorth();
	void SpawnSouth();
	void SpawnEast();
	void SpawnWest();
private:
	float x, y, angle, ttl;
};

