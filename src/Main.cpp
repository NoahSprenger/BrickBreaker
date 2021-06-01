#include "Ball.cpp"
#include "Barriers.cpp"
#include "Paddle.cpp"
#include "physics.h"

int main()
{
#if defined(_DEBUG)
	std::cout << "Debugging!" << std::endl;
#endif

	sf::RenderWindow window(sf::VideoMode(1200.0f, 675.0f), "Brick Breaker", sf::Style::Default);
	b2World world(b2Vec2(0.0, 0.0));
	window.setFramerateLimit(60);

	// From Barriers.cpp
	Barriers barrier1(world, window);
	// From Ball.cpp
	Ball b1(world, 200, 200, 20, 250, 45);
	b1.setFillColor(sf::Color::Red);
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
		p1.updatePosition(window);
		b1.updatePosition();
		if (b1.checkCollision(p1))
		{
			std::cout << b1.getPosition().x << std::endl;
		}
		barrier1.updateBarriers(b1.body);
		window.clear();
		world.Step(1.0 / 60, int32(8), int32(3));
		window.draw(b1);
		window.display();
	}
	return 0;
}