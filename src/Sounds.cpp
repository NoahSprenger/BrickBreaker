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
		menu.openFromFile("content/TitleTheme.ogg");
		main.openFromFile("content/main.ogg");
		menu.setLoop(true);
		main.setLoop(true);
	}
	void play_ball()
	{
		ball.play();
	}
	void play_menu()
	{
		menu.play();
	}
	void stop_menu()
	{
		menu.stop();
	}
	void play_main()
	{
		main.play();
	}
	void stop_main()
	{
		main.stop();
	}
	sf::SoundBuffer ball_buffer, death_buffer;
	sf::Sound ball, death;
	sf::Music menu, main;
};

#endif