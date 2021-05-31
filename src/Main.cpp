#include "Ball.cpp"
#include "Paddle.cpp"
#include "physics.h"
#include <SFML/Graphics.hpp>

int main()
{
#if defined(_DEBUG)
	std::cout << "Debugging!" << std::endl;
#endif

	sf::RenderWindow window(sf::VideoMode(1200.0f, 675.0f), "Boiler box2d", sf::Style::Default);
	b2World world(b2Vec2(0.0, 0.0));
	window.setFramerateLimit(60);

	// Add boundaries that are hidden
	physics::createBox(world, 0, window.getSize().y, window.getSize().x, 20, b2_staticBody); // floor
	physics::createBox(world, window.getSize().x, 0, 20, window.getSize().y, b2_staticBody); // right wall
	physics::createBox(world, 0, -20, window.getSize().x, 20, b2_staticBody); // roof
	physics::createBox(world, -20, 0, 20, window.getSize().y, b2_staticBody); // left wall

	// From Ball.cpp
	Ball b1(world, 200, 200, 20, 250, 45);
	physics::setBlockColor(b1.body, sf::Color::Red);
	// From Paddle.cpp
	Paddle p1(world, 20, 550, 100, 10);

	while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				physics::createBox(world, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, 20, 20);
			}
		}
		p1.updatePosition();
		b1.updatePosition();

		window.clear();
		window.draw(b1);
		physics::displayWorld(world, window);
		window.display();
	}

	return 0;
}