#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Menu
{
private:
	/* data */
public:
	Menu(/* args */);
	~Menu();
	int Run_Menu();
	void run(sf::RenderWindow& window, sf::Sprite& runner, int& counter, int& x, bool& movingright);
	sf::RenderWindow menu_window;
	sf::CircleShape easy_mode;
	sf::CircleShape normal_mode;
	sf::CircleShape hard_mode;
	sf::Font arial;
	sf::Texture trump_tex;
	sf::Text easy_text, normal_text, hard_text, greeting;
	sf::Sprite trump;
	int counter = 0;
	int x = 0;
	bool movingright = true;
};

Menu::Menu(/* args */)
{
	menu_window.create(sf::VideoMode(1920.0f, 1080.0f), "Main Menu", sf::Style::Default);
	menu_window.setFramerateLimit(60);
	int button_placement_x = (menu_window.getSize().x / 3) - 200;
	int button_placement_y = (menu_window.getSize().y / 3) - 200;
	arial.loadFromFile("content/arial.ttf");
	easy_text.setFont(arial);
	easy_text.setCharacterSize(20);
	easy_text.setPosition(button_placement_x, button_placement_y - 40);
	easy_text.setString("Easy");
	normal_text.setFont(arial);
	normal_text.setCharacterSize(20);
	normal_text.setPosition(button_placement_x * 2, button_placement_y - 40);
	normal_text.setString("Normal");
	hard_text.setFont(arial);
	hard_text.setCharacterSize(20);
	hard_text.setPosition(button_placement_x * 3, button_placement_y - 40);
	hard_text.setString("Hard");
	greeting.setFont(arial);
	greeting.setCharacterSize(50);
	greeting.setPosition(button_placement_x * 2 - 100, button_placement_y + 300);
	greeting.setString("Punch Trump");
	easy_mode.setFillColor(sf::Color::Green);
	easy_mode.setPosition(button_placement_x, button_placement_y);
	easy_mode.setRadius(50);
	normal_mode.setFillColor(sf::Color::White);
	normal_mode.setPosition(button_placement_x * 2, button_placement_y);
	normal_mode.setRadius(50);
	hard_mode.setFillColor(sf::Color::Red);
	hard_mode.setPosition(button_placement_x * 3, button_placement_y);
	hard_mode.setRadius(50);
	trump_tex.loadFromFile("content/TrumpSprite.png");
	trump.setTexture(trump_tex);
	trump.setPosition(sf::Vector2f(0, menu_window.getSize().y - 260));
	trump.setTextureRect(sf::IntRect(0, 0, 250, 250));
}

Menu::~Menu()
{
	menu_window.close();
}

// Deals with the miner running (animation, movement)
void Menu::run(sf::RenderWindow& window, sf::Sprite& runner, int& counter, int& x, bool& movingright)
{
	counter += 10;
	if (counter > 2250)
	{
		counter = 0;
	}
	if (counter % 250 == 0)
		runner.setTextureRect(sf::IntRect(counter, 0, 250, 250));

	if (runner.getPosition().x < window.getSize().x && movingright)
	{
		x = 1;
	}
	else
	{
		movingright = false;
		x = -1;
		if (runner.getPosition().x < 0)
			movingright = true;
	}
	runner.move(x, 0);
}

int Menu::Run_Menu()
{
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	while (menu_window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		mousePosWindow = sf::Mouse::getPosition(menu_window);
		mousePosView = menu_window.mapPixelToCoords(mousePosWindow);
		sf::Event event;
		while (menu_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				menu_window.close();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				// add boxes to click
				if (mousePosView.x > easy_mode.getPosition().x && mousePosView.x < easy_mode.getPosition().x + easy_mode.getRadius() * 2 && mousePosView.y > easy_mode.getPosition().y && mousePosView.y < easy_mode.getPosition().y + easy_mode.getRadius() * 2)
				{
					menu_window.close();
					return 1;
				}
				if (mousePosView.x > normal_mode.getPosition().x && mousePosView.x < normal_mode.getPosition().x + normal_mode.getRadius() * 2 && mousePosView.y > normal_mode.getPosition().y && mousePosView.y < normal_mode.getPosition().y + normal_mode.getRadius() * 2)
				{
					menu_window.close();
					return 2;
				}
				if (mousePosView.x > hard_mode.getPosition().x && mousePosView.x < hard_mode.getPosition().x + hard_mode.getRadius() * 2 && mousePosView.y > hard_mode.getPosition().y && mousePosView.y < hard_mode.getPosition().y + hard_mode.getRadius() * 2)
				{
					menu_window.close();
					return 3;
				}
			}
		}
		run(menu_window, trump, counter, x, movingright);
		menu_window.clear();
		menu_window.draw(easy_text);
		menu_window.draw(normal_text);
		menu_window.draw(hard_text);
		menu_window.draw(greeting);
		menu_window.draw(easy_mode);
		menu_window.draw(normal_mode);
		menu_window.draw(hard_mode);
		menu_window.draw(trump);
		menu_window.display();
	}
	return 0;
}
#endif