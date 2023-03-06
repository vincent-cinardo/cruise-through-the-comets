#pragma once
#include "Controller.h"
#include "ResourceManager.h"

class Spaceship
{
public:
	Spaceship();
	~Spaceship();
	void Move(float dx, float dy);
	void SetPos(float x, float y);
	void SetTexture(Texture& texture);
	float GetX();
	float GetY();
	float GetSize();
	Texture& GetSprite();
	Texture& GetSpriteLose();
private:
	int health;
	float x, y, size;
	Texture currentTexture;
};