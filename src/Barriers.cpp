#ifndef Barriers_H
#define Barriers_H
#include "physics.h"

struct Barriers
{
	Barriers(b2World& world, sf::RenderWindow& window)
	{
		// Add boundaries that are hidden
		floor = physics::createBox(world, 0, window.getSize().y, window.getSize().x, 20, b2_staticBody); // floor
		wallR = physics::createBox(world, window.getSize().x, 0, 20, window.getSize().y, b2_staticBody); // right wall
		roof = physics::createBox(world, 0, -20, window.getSize().x, 20, b2_staticBody);				 // roof
		wallL = physics::createBox(world, -20, 0, 20, window.getSize().y, b2_staticBody);				 // left wall
	}
	void updateBarriers(b2Body* ball)
	{
		if (physics::checkCollision(floor, ball))
		{
			std::cout << "Death\n";
			// End game function (death screen, noise, etc)
		}

		// use this for barriers to hit
	}
	Block floor, wallR, roof, wallL;
};

#endif