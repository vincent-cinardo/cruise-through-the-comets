#pragma once
#include <iostream>
#include <random>
class MathHelper
{
public:
	static float Random(float min, float max);
	static int Random(int min, int max);
private:
	MathHelper();
};

