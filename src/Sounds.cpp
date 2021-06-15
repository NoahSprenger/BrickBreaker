#ifndef SOUNDS_H
#define SOUNDS_H
#include "physics.h"
#include <SFML/Audio.hpp>

struct Sounds
{
	Sounds(b2World& world, sf::RenderWindow& window)
	{
		ball_buffer.loadFromFile("content/ball.wav");
		ball.setBuffer(ball_buffer);
	}
	void play_ball()
	{
		ball.play();
	}
	sf::SoundBuffer ball_buffer;
	sf::Sound ball;
};

#endif