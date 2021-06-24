#ifndef TEXT_H
#define TEXT_H
#include <SFML/Graphics.hpp>

struct Text : public sf::Text
{
	Text()
	{
		arcade.loadFromFile("content/ka1.ttf");
		this->setFont(arcade);
		this->setCharacterSize(20);
		this->setFillColor(sf::Color::Red);
	}
	// Update the text and the position of it
	void update_text(sf::RenderWindow& render, sf::Vector2f position, std::string words)
	{
		this->setPosition(position);
		this->setString(words);
		render.draw(*this);
	}
	sf::Text score;
	sf::Font arcade;
};

#endif