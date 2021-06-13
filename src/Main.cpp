#include "Ball.cpp"
#include "Barriers.cpp"
#include "Brick.cpp"
#include "Menu.h"
#include "Paddle.cpp"
#include "physics.h"
#include <imgui/imgui-SFML.h>
#include <imgui/imgui.h>
#include <vector>

int main()
{
#if defined(_DEBUG)
	std::cout << "Debugging!" << std::endl;
#endif

	Menu menu;
	switch (menu.Run_Menu())
	{
		case 1:
			/* code */
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
	}
	sf::RenderWindow window;
	window.create(sf::VideoMode(1200.0f, 675.0f), "Brick Breaker", sf::Style::Default);
	b2World world(b2Vec2(0.0, 0.0));
	window.setFramerateLimit(60);
	// From Barriers.cpp
	Barriers barrier(world, window);
	// From Ball.cpp
	Ball b1(world, 200, 200, 20, 250, 45);
	b1.setFillColor(sf::Color::Red);
	// From Paddle.cpp
	Paddle p1(world, 20, 550, 100, 10);
	std::vector<Brick> bricks;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			bricks.push_back(Brick(world, 40 + i * 120, 40 + j * 30, 60, 20));
			bricks.back().setFillColor(sf::Color::Cyan);
		}
	}

	// ImGui fun
	bool settings = false;
	ImGui::SFML::Init(window);
	sf::Clock deltaClock;
	while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		sf::Event event;
		ImGui::SFML::Update(window, deltaClock.restart());
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		// Outside of event loop because of tearing issue with imgui window
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11) || settings)
		{
			settings = true;
			ImGui::Begin("Settings");
			if (ImGui::Button("Fullscreen"))
			{
				window.close();
				window.create(sf::VideoMode(1920.0f, 1080.0f), "Brick Breaker", sf::Style::Fullscreen);
				window.setFramerateLimit(60);
				// Still need to resize the game area (paddle, boxes, floor, sides, etc)
			}
			if (ImGui::Button("Default"))
			{
				window.close();
				window.create(sf::VideoMode(1200.0f, 675.0f), "Brick Breaker", sf::Style::Default);
				window.setFramerateLimit(60);
				// Still need to resize the game features
			}
			ImGui::End();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F12))
		{
			settings = false;
		}
		b1.checkCollision(p1);
		b1.deathCollision(barrier.barriers[0]);
		// Brick loop
		window.clear();
		world.Step(1.0 / 60, int32(8), int32(3));
		p1.updatePosition(window);
		b1.updatePosition(window);
		for (long unsigned int i = 0; i < bricks.size(); i++)
		{
			if (b1.checkCollision(bricks[i]))
			{
				world.DestroyBody(bricks[i].body);
				bricks.erase(bricks.begin() + i);
			}
		}
		for (auto i : bricks)
		{ // I like this way
			i.updatePosition(window);
		}
		ImGui::SFML::Render(window);
		window.display();
	}
	ImGui::SFML::Shutdown();
	return 0;
}