#ifndef MENU_H
#define MENU_H
#include "Sounds.cpp"
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
	sf::RenderWindow menu_window;
	sf::CircleShape easy_mode;
	sf::CircleShape normal_mode;
	sf::CircleShape hard_mode;
	sf::Font arcade;
	sf::Text easy_text, normal_text, hard_text, greeting, info;
};

Menu::Menu(/* args */)
{
	menu_window.create(sf::VideoMode(1920.0f, 1080.0f), "Main Menu", sf::Style::Default);
	menu_window.setFramerateLimit(60);
	int button_placement_x = (menu_window.getSize().x / 3) - 200;
	int button_placement_y = (menu_window.getSize().y / 3) - 200;
	arcade.loadFromFile("content/ka1.ttf");
	easy_text.setFont(arcade);
	easy_text.setCharacterSize(50);
	easy_text.setPosition(button_placement_x, button_placement_y - 100);
	easy_text.setString("Easy");
	normal_text.setFont(arcade);
	normal_text.setCharacterSize(50);
	normal_text.setPosition(button_placement_x * 2, button_placement_y - 100);
	normal_text.setString("Normal");
	hard_text.setFont(arcade);
	hard_text.setCharacterSize(50);
	hard_text.setPosition(button_placement_x * 3, button_placement_y - 100);
	hard_text.setString("Hard");
	greeting.setFont(arcade);
	greeting.setCharacterSize(100);
	greeting.setPosition(button_placement_x * 2 - 450, button_placement_y + 300);
	greeting.setString("Brick Breaker");
	easy_mode.setFillColor(sf::Color::Green);
	easy_mode.setPosition(button_placement_x, button_placement_y);
	easy_mode.setRadius(50);
	normal_mode.setFillColor(sf::Color::White);
	normal_mode.setPosition(button_placement_x * 2, button_placement_y);
	normal_mode.setRadius(50);
	hard_mode.setFillColor(sf::Color::Red);
	hard_mode.setPosition(button_placement_x * 3, button_placement_y);
	hard_mode.setRadius(50);
	info.setFont(arcade);
	info.setCharacterSize(25);
	info.setPosition(button_placement_x * 2 - 400, button_placement_y * 2 + 325);
	info.setString("Press F11 to open the menu while in game\n and F12 to close the menu");
}

Menu::~Menu()
{
	menu_window.close();
}

int Menu::Run_Menu()
{
	Sounds music;
	music.play_menu();
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
		menu_window.clear();
		menu_window.draw(info);
		menu_window.draw(easy_text);
		menu_window.draw(normal_text);
		menu_window.draw(hard_text);
		menu_window.draw(greeting);
		menu_window.draw(easy_mode);
		menu_window.draw(normal_mode);
		menu_window.draw(hard_mode);
		menu_window.display();
	}
	music.stop_menu();
	return 0;
}
#endif