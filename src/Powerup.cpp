#ifndef POWERUP_H
#define POWERUP_H
#include "Ball.cpp"
#include "Paddle.cpp"
#include <box2d/box2d.h>
#include <iostream>

struct Powerup
{
	Powerup()
	{
		srand(std::time(NULL));
	}
	void select_powerup(b2World& world, int dif, int r, Ball& ball, Paddle& p1)
	{
		switch (rand_power)
		{
			case 0:
				p1.faster_paddle();
				break;
			case 1:
				ball.big_ball(world, dif, r, ball.body->GetAngle());
				break;
			case 2:
				p1.updateSize(world, 300);
				break;
			case 3:
				std::cout << "another powerup" << std::endl;
				break;
			default:
				break;
		}
	}
	void reset(b2World& world, sf::RenderWindow& window, int dif, Paddle& p1, Ball& ball)
	{
		switch (rand_power)
		{
			case 0:
				p1.regular_speed();
				break;
			case 1:
				ball.resize_in_game(world, window, dif, p1);
				break;
			case 2:
				p1.resize(world, window);
			default:
				break;
		}
		rand_power = rand() % 4;
		std::cout << rand_power << std::endl;
	}
	int rand_power;
};

#endif