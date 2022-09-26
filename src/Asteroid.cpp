#include "Asteroid.h"

//Spawn an asteroid offscreen, which shoots at a random time and a random angle in degrees. It will be deleted after 10 seconds.
Asteroid::Asteroid()
{
	ttl = 10.0f;
	srand(std::time(nullptr));
	int num = (int) rand() % 4;

	switch (num)
	{
	case 0:
		SpawnNorth();
		break;
	case 1:
		SpawnSouth();
		break;
	case 2:
		SpawnEast();
		break;
	case 3:
		SpawnWest();
		break;
	}
}

void Asteroid::Update(float dt)
{
	ttl -= dt;
	Move(dt);
}

//Asteroids store angles opposite to their posiition, the direction they will be going towards the center.
void Asteroid::Move(float dt)
{
	//May want to multiply a magnitude as well
	x += x * cos(angle) * dt;
	y += y * sin(angle) * dt;
}

void Asteroid::Hit()
{

}

void Asteroid::SpawnNorth()
{
	srand(std::time(nullptr));

	float factor;
	int negate = (rand()) % 2;
	if (negate)
	{
		factor = 1.0f;
	}
	else factor = -1.0f;

	y = 11.0f;
	x = (float)(rand() * 11) / (float) RAND_MAX;
	angle = 270.0f + negate;
}
void Asteroid::SpawnSouth()
{
	srand(std::time(nullptr));
	float factor;
	int negate = (rand()) % 2;
	if (negate)
	{
		factor = 1.0f;
	}
	else factor = -1.0f;

	y = -11.0f;
	x = (float)(rand() * 11) / (float)RAND_MAX;
	angle = 90.0f + ((float)((rand() / RAND_MAX) % 15) * negate);
}
void Asteroid::SpawnEast()
{
	srand(std::time(nullptr));
	float factor;
	int negate = (rand()) % 2;
	if (negate)
	{
		factor = 1.0f;
	}
	else factor = -1.0f;

	x = 11.0f;
	y = (float)(rand() * 11) / (float)RAND_MAX;
	angle = 180.0f + ((float)((rand() / RAND_MAX) % 15) * negate);
}
void Asteroid::SpawnWest()
{
	srand(std::time(nullptr));
	float factor;
	int negate = (rand()) % 2;
	if (negate)
	{
		factor = 1.0f;
	}
	else factor = -1.0f;

	x = -11.0f;
	y = ((float)((rand() / RAND_MAX) % 15) * negate);
}
