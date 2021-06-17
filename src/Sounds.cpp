#ifndef SOUNDS_H
#define SOUNDS_H
#include "physics.h"
#include <SFML/Audio.hpp>

struct Sounds
{
	Sounds()
	{
		ball_buffer.loadFromFile("content/ball.wav");
		ball.setBuffer(ball_buffer);
	}
	void play_ball()
	{
		ball.play();
	}
	sf::SoundBuffer ball_buffer, death_buffer;
	sf::Sound ball, death;
};

#endif