#include "Ball.cpp"
#include "Barriers.cpp"
#include "Brick.cpp"
#include "Menu.h"
#include "Paddle.cpp"
#include "physics.h"
#include <vector>

int main()
{
#if defined(_DEBUG)
	std::cout << "Debugging!" << std::endl;
#endif

	Menu menu;
	menu.Run_Menu();
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
	// Brick bricks(world, 40, 40, 60, 20);
	std::vector<Brick> bricks;
	for (int i = 0; i < 10; i++)
	{
		std::cout << i << std::endl;
		bricks.push_back(Brick(world, 40 + i * 120, 40, 60, 20));
		bricks.back().setFillColor(sf::Color::Cyan);
	}
	while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		b1.checkCollision(p1);
		// Brick loop
		window.clear();
		world.Step(1.0 / 60, int32(8), int32(3));
		p1.updatePosition(window);
		b1.updatePosition(window);
		barrier1.updateBarriers(b1.body); // refactor to be like the others so you don't have to call anything from physics.h
		for (long unsigned int i = 0; i < bricks.size(); i++)
		{
			bricks[i].updatePosition(window);
			if (b1.checkCollision(bricks[i]))
			{
				world.DestroyBody(bricks[i].body);
				bricks.erase(bricks.begin() + i);
			}
		}
		window.display();
	}
	return 0;
}