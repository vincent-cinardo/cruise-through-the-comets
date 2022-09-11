#pragma once
class Alien
{
	enum Genetics {
		None,
		Fish,
		Dog,
		Human,
		Ape,
	};

	enum Parts {
		Head,
		Torso,
		Arms,
		Legs
	};

public:
	Alien();
	Alien(float x, float y);
	~Alien();
	void Move(float x, float y);

private:
	float health[4];
	float stamina;
	float x, y;
};

