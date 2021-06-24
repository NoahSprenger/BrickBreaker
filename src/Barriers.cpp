#ifndef Barriers_H
#define Barriers_H
#include "Paddle.cpp"

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
	// For when window is resized
	void resize(b2World& world, sf::RenderWindow& window)
	{
		for (long unsigned int i = 0; i < barriers.size(); i++)
		{
			world.DestroyBody(barriers[i].body);
		}
		barriers.clear();
		Paddle floor(world, 0, window.getSize().y, window.getSize().x, 20);
		barriers.push_back(floor);
		Paddle wallR(world, window.getSize().x, 0, 20, window.getSize().y);
		barriers.push_back(wallR);
		Paddle roof(world, 0, -20, window.getSize().x, 20);
		barriers.push_back(roof);
		Paddle wallL(world, -20, 0, 20, window.getSize().y);
		barriers.push_back(wallL);
	}
	std::vector<Paddle> barriers;
};

#endif