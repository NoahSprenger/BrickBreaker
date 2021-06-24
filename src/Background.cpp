#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <SFML/Graphics.hpp>

struct Background : public sf::Sprite
{
	Background(sf::RenderWindow& window)
	{
		back_txt.loadFromFile("content/bestback.jpg");
		back2_txt.loadFromFile("content/background.png");
		back3_txt.loadFromFile("content/back.jpg");
		back4_txt.loadFromFile("content/back4.jpg");
		this->setTexture(back_txt);
		x_scale = (float)window.getSize().x / 1920, y_scale = (float)window.getSize().y / 1080;
		this->setScale(sf::Vector2f(x_scale, y_scale));
	}
	void update(sf::RenderWindow& render)
	{
		render.draw(*this);
	}
	void new_background(int level)
	{
		// number dosen't need to be random, it just needs to cycle through
		switch (level)
		{
			case 1:
				this->setTexture(back_txt);
				break;
			case 2:
				this->setTexture(back2_txt);
				break;
			case 3:
				this->setTexture(back3_txt);
				break;
			case 4:
				this->setTexture(back4_txt);
				break;
			default:
				this->setTexture(back3_txt);
				break;
		}
	}
	void resize(sf::RenderWindow& window)
	{
		x_scale = (float)window.getSize().x / 1920, y_scale = (float)window.getSize().y / 1080;
		this->setScale(sf::Vector2f(x_scale, y_scale));
	}
	float x_scale, y_scale;
	sf::Texture back_txt, back2_txt, back3_txt, back4_txt;
};

#endif