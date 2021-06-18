#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <SFML/Graphics.hpp>

struct Background : public sf::Sprite
{
	Background(sf::RenderWindow& window)
	{
		back_txt.loadFromFile("content/bestback.jpg");
		this->setTexture(back_txt);
		x_scale = (float)window.getSize().x / 1920, y_scale = (float)window.getSize().y / 1080;
		this->setScale(sf::Vector2f(x_scale, y_scale));
	}
	void update(sf::RenderWindow& render)
	{
		render.draw(*this);
	}
	void resize(sf::RenderWindow& window)
	{
		x_scale = (float)window.getSize().x / 1920, y_scale = (float)window.getSize().y / 1080;
		this->setScale(sf::Vector2f(x_scale, y_scale));
	}
	float x_scale, y_scale;
	sf::Texture back_txt;
};

#endif