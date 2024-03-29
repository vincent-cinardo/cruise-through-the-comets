#include "Asteroid.h"

//Spawn an asteroid offscreen, which shoots in a random direction towards the center. It will be deleted after 10 seconds.
Asteroid::Asteroid()
{
	size = 0.8f;
	ttl = 10.0f;
	int num = MathHelper::Random(0, 3);
	angularVel = MathHelper::Random(-25.0f, 25.0f);
	spriteAngle = MathHelper::Random(-5.0f, 5.0f);

	//Angle in degrees -> radians.
	switch (num)
	{
	case 0:
		//North
		spawnLoc = "north";
		y = 11.0f;
		x = (float)(MathHelper::Random(-5.5f, 5.5f));
		angle = (270.0f + ((float)(MathHelper::Random(-20, 20)))) * 0.01745329251;
		break;
	case 1:
		//South
		spawnLoc = "south";
		y = -11.0f;
		x = (float)(MathHelper::Random(-5.5f, 5.5f));
		angle = (90.0f + ((float)(MathHelper::Random(-20, 20)))) * 0.01745329251;
		break;
	case 2:
		//East
		spawnLoc = "east";
		x = 11.0f;
		y = (float)(MathHelper::Random(-5.5f, 5.5f));
		angle = (180.0f + ((float)(MathHelper::Random(-20, 20)))) * 0.01745329251;
		break;
	case 3:
		//West
		spawnLoc = "west";
		x = -11.0f;
		y = (float)(MathHelper::Random(-5.5f, 5.5f));
		angle = (((float)(MathHelper::Random(-20, 20)))) * 0.01745329251;
		break;
	}
}

void Asteroid::Update(float dt)
{
	ttl -= dt;
	Move(dt);
}

//Move the asteroid towards the center and spin according to the randomly generated angular velocity.
void Asteroid::Move(float dt)
{
	x += 5.0f * cos(angle) * dt;
	y += 5.0f * sin(angle) * dt;
	spriteAngle += angularVel * dt;
}

float Asteroid::GetSpriteAngle()
{
	return spriteAngle;
}

float Asteroid::GetAngularVelocity()
{
	return angularVel;
}
	
float Asteroid::GetX()
{
	return x;
}

float Asteroid::GetY()
{
	return y;
}

float Asteroid::GetSize()
{
	return size;
}

const char* Asteroid::SpawnedFrom()
{
	return spawnLoc;
}