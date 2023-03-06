#include "Spaceship.h"

Spaceship::Spaceship()
{
	x = 0;
	y = 0;
	health = 3;
	size = 0.5f;
	currentTexture = ResourceManager::GetTexture("spaceship");
}

Spaceship::~Spaceship() {}

void Spaceship::Move(float dx, float dy)
{
	x += dx;
	y += dy;
}

void Spaceship::SetTexture(Texture& texture)
{
	this->currentTexture = texture;
}

void Spaceship::SetPos(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Spaceship::GetX()
{
	return x;
}

float Spaceship::GetY()
{
	return y;
}

float Spaceship::GetSize()
{
	return size;
}

Texture& Spaceship::GetSprite()
{
	//Y input takes precedence

	if (Controller::inputY != 0)
	{
		currentTexture = (Controller::inputY == 1) ? ResourceManager::GetTexture("spaceship") : ResourceManager::GetTexture("spaceship2");
		return currentTexture;
	}

	if (Controller::inputX != 0)
	{
		currentTexture = (Controller::inputX == 1) ? ResourceManager::GetTexture("spaceship1") : ResourceManager::GetTexture("spaceship3");
		return currentTexture;
	}

	return currentTexture;
}

Texture& Spaceship::GetSpriteLose()
{
	return currentTexture;
}