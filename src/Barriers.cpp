#ifndef Barriers_H
#define Barriers_H
#include "Paddle.cpp"
#include "physics.h"

struct Barriers
{
	Barriers(b2World& world, sf::RenderWindow& window)
	{
		// Add boundaries that are hidden
		Paddle floor(world, 0, window.getSize().y, window.getSize().x, 20);
		barriers.push_back(floor);
		Paddle wallR(world, window.getSize().x, 0, 20, window.getSize().y);
		barriers.push_back(wallR);
		Paddle roof(world, 0, -20, window.getSize().x, 20);
		barriers.push_back(roof);
		Paddle wallL(world, -20, 0, 20, window.getSize().y);
		barriers.push_back(wallL);
	}
	void updateBarriers()
	{
		// use this for barriers to hit
	}
	std::vector<Paddle> barriers;
};

#endif