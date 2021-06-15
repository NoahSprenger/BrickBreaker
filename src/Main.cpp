#include "Ball.cpp"
#include "Barriers.cpp"
#include "Brick.cpp"
#include "Menu.h"
#include "Paddle.cpp"
#include "Sounds.cpp"
#include "physics.h"
#include <imgui/imgui-SFML.h>
#include <imgui/imgui.h>
#include <vector>

int main()
{
#if defined(_DEBUG)
	std::cout << "Debugging!" << std::endl;
#endif
	std::vector<Brick> bricks;
	b2World world(b2Vec2(0.0, 0.0));
	Menu menu;
	switch (menu.Run_Menu())
	{
		case 1:
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 1; j++)
				{
					bricks.push_back(Brick(world, 40 + i * 120, 40 + j * 30, 60, 20));
					bricks.back().setFillColor(sf::Color::Cyan);
				}
			}
			break;
		case 2:
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					bricks.push_back(Brick(world, 40 + i * 120, 40 + j * 30, 60, 20));
					bricks.back().setFillColor(sf::Color::Cyan);
					// physics::setCollisionID(bricks.back().body, -1); // try and get to smash through the bricks
				}
			}
			break;
		case 3:
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					bricks.push_back(Brick(world, 40 + i * 120, 40 + j * 30, 60, 20));
					bricks.back().setFillColor(sf::Color::Cyan);
				}
			}
			break;
		default:
			break;
	}
	sf::RenderWindow window;
	window.create(sf::VideoMode(1200.0f, 675.0f), "Brick Breaker", sf::Style::Default);
	window.setFramerateLimit(60);
	// From Barriers.cpp
	Barriers barrier(world, window);
	// From Ball.cpp
	Ball b1(world, 200, 200, 20, 250, 45);
	b1.setFillColor(sf::Color::Red);
	// physics::setCollisionID(b1.body, -1);
	// From Paddle.cpp
	Paddle p1(world, 20, window.getSize().y * 0.9, 100, 10);
	// Sound stuff
	Sounds ball(world, window);
	// Counters
	int powerup = 0;
	bool isPowerup = false;
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
			if (event.type == sf::Event::KeyReleased)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					p1.updateSize(world, 400);
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
				barrier.resize(world, window);
				p1.resize(world, window);
				// no need to resize ball into the window
			}
			if (ImGui::Button("Default"))
			{
				window.close();
				window.create(sf::VideoMode(1200.0f, 675.0f), "Brick Breaker", sf::Style::Default);
				window.setFramerateLimit(60);
				barrier.resize(world, window);
				p1.resize(world, window);
				// Still need to resize ball into the window
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
				ball.play_ball();
				world.DestroyBody(bricks[i].body);
				bricks.erase(bricks.begin() + i);
				powerup++;
				if (powerup == 5) {
					p1.updateSize(world, 300);
				}
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