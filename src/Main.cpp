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
	int dif = menu.Run_Menu();
	bricks[0].refill_vector(world, dif, bricks);
	sf::RenderWindow window;
	window.create(sf::VideoMode(1200.0f, 675.0f), "Brick Breaker", sf::Style::Default);
	window.setFramerateLimit(60);
	// From Barriers.cpp
	Barriers barrier(world, window);
	// From Ball.cpp
	Ball b1(world, window.getSize().x / 2, 300, 20, 250 * dif, 90);
	// physics::setCollisionID(b1.body, -1);
	// From Paddle.cpp
	Paddle p1(world, window.getSize().x / 2 - 50, window.getSize().y * 0.9, 100, 10);
	// Sound stuff
	Sounds ball;
	// Counters
	int powerup = 0;
	// ImGui fun
	bool settings = false;
	ImGui::SFML::Init(window);
	sf::Clock deltaClock;
	sf::Event event;
	while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		ImGui::SFML::Update(window, deltaClock.restart());
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		// Outside of event loop because of tearing issue with imgui window.
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
			if (ImGui::Button("Quit")) {
				window.close();
			}
			ImGui::End();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F12))
		{
			settings = false;
		}
		b1.checkCollision(p1);
		// Brick loop
		window.clear();
		world.Step(1.0 / 60, int32(8), int32(3));
		if (bricks.empty())
		{
			bricks[0].refill_vector(world, dif, bricks);
		}
		b1.deathCollision(world, window, barrier.barriers[0], powerup, b1, p1, bricks, dif);
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
				// Use a random number between 5 and 10 to do a random powerup (create more powerups)
				switch (powerup)
				{
					case 2:
						p1.faster_paddle();
						break;
					case 5:
						p1.updateSize(world, 300);
						break;
					case 10:
						p1.updateSize(world, 100);
					default:
						break;
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