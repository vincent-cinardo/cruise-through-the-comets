#pragma once
#include "Controller.h"
#include "ResourceManager.h"

class Glooper
{
public:
	Glooper();
	~Glooper();
	void Move(float dx, float dy);
	void SetPos(float x, float y);
	void Hurt();
	void Die();
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

