#pragma once
#include <iostream>
#include "MathHelper.h"

//Matrix/vector math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Asteroid
{
public:
	Asteroid();
	void Update(float dt);
	void Move(float dt);
	float GetSpriteAngle();
	float GetAngularVelocity();
	float GetX();
	float GetY();
	float GetSize();
	const char* SpawnedFrom();
	float ttl;
private:
	const char* spawnLoc;
	float x, y, angle, angularVel, spriteAngle, size;
	
};

