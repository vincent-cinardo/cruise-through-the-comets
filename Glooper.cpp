#include "Glooper.h"

Glooper::Glooper()
{
	health = 3;
	x = 0;
	y = 0;
	size = 0.5f;
	currentTexture = ResourceManager::GetTexture("stick");
}

Glooper::~Glooper()
{

}

void Glooper::Move(float dx, float dy)
{
	x += dx;
	y += dy;
}

void Glooper::Hurt()
{
	if (health > 0)
		health--;
	else
		Die();
}

void Glooper::Die()
{

}

float Glooper::GetX()
{
	return x;
}

float Glooper::GetY()
{
	return y;
}

float Glooper::GetSize()
{
	return size;
}

Texture& Glooper::GetSprite()
{
	//Y input takes precedence

	if (Controller::inputY != 0)
	{
		currentTexture = (Controller::inputY == 1) ? ResourceManager::GetTexture("stick") : ResourceManager::GetTexture("stick2");
		return currentTexture;
	}

	if (Controller::inputX != 0)
	{
		currentTexture = (Controller::inputX == 1) ? ResourceManager::GetTexture("stick1") : ResourceManager::GetTexture("stick3");
		return currentTexture;
	}

	return currentTexture;
}
