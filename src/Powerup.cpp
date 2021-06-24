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
		srand(std::time(NULL)); // Randomize the seed
	}
	// Selects a random power up
	void select_powerup(b2World& world, int dif, int r, Ball& ball, Paddle& p1)
	{
		switch (rand_power)
		{
			case 0:
				p1.faster_paddle();
				words = "Faster Paddle";
				break;
			case 1:
				ball.big_ball(world, dif, r, ball.body->GetAngle());
				words = "Bigger Ball";
				break;
			case 2:
				p1.updateSize(world, 300);
				words = "Bigger Paddle";
				break;
			case 3:
				ball.slow();
				words = "Slow Ball";
				break;
			case 4:
				ball.no_death(true);
				words = "No Death";
				break;
			default:
				words = "";
				break;
		}
	}
	// Resets the power up
	void reset(b2World& world, sf::RenderWindow& window, int dif, Paddle& p1, Ball& ball)
	{
		switch (rand_power)
		{
			case 0:
				p1.regular_speed();
				break;
			case 1:
				ball.resize_in_game(world, window, dif);
				break;
			case 2:
				p1.resize(world, window);
				break;
			case 3:
				ball.speed = 250 * dif;
				break;
			case 4:
				ball.no_death(false);
			default:
				break;
		}
		rand_power = rand() % 5;
	}
	std::string words;
	int rand_power;
};

#endif