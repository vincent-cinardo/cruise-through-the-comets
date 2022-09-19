#pragma once
class Glooper
{
public:
	Glooper();
	~Glooper();
	void Move(float dx, float dy);
	void Hurt();
	void Die();
private:
	int health;
	float x, y;
};

