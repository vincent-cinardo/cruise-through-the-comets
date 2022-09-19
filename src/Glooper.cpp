#include "Glooper.h"

Glooper::Glooper()
{
	health = 3;
	x = 0;
	y = 0;
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
