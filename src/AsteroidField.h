#pragma once
#include <iostream>
#include <vector>
#include "Asteroid.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "MathHelper.h"

class AsteroidField
{
public:
	AsteroidField();
	~AsteroidField();
	void SpawnAsteroid();
	void UpdateAsteroids(float dt);
	void DeleteAsteroid(Asteroid* asteroid);
	void Render(SpriteRenderer* renderer);
private:
	std::vector<Asteroid*> asteroids;
	float nextAsteroidSpawn;
	const char* lastSpawn;
};

