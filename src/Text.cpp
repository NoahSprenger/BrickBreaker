#ifndef TEXT_H
#define TEXT_H
#include "physics.h"
#include <SFML/Graphics.hpp>

struct Text : public sf::Text
{
	Text(sf::RenderWindow& window)
	{
		arcade.loadFromFile("content/ka1.ttf");
		this->setFont(arcade);
		this->setCharacterSize(20);
		this->setColor(sf::Color::Red);
		this->setPosition(sf::Vector2f(10, window.getSize().y * 0.9));
	}
	void update_text(sf::RenderWindow& render, int hold)
	{
		this->setString("Score " + std::to_string(hold));
		render.draw(*this);
	}
	void resize(sf::RenderWindow& window)
	{
		this->setPosition(sf::Vector2f(10, window.getSize().y * 0.9));
	}
	sf::Text score;
	sf::Font arcade;
};

#endif