// ! TO DO ! //
/* multiple lives and levels,
powerups,
add textures to make it more visually appealing,
update how to play or make a tutorial,
add french support, create a pause function to pause the game,
a system to unlock backgrounds etc (if I get everything else done)*/
#include "Background.cpp"
#include "Ball.cpp"
#include "Barriers.cpp"
#include "Brick.cpp"
#include "ImGuiStuff.cpp"
#include "Menu.h"
#include "Paddle.cpp"
#include "Powerup.cpp"
#include "Sounds.cpp"
#include "Text.cpp"
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
	sf::RenderWindow window;
	window.create(sf::VideoMode(1200.0f, 675.0f), "Brick Breaker", sf::Style::Default);
	bricks[0].refill_vector(world, window, dif, bricks);
	window.setVerticalSyncEnabled(true);
	// window.setFramerateLimit(60);
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
	int level = 1;
	// Text
	Text text;
	Text pwrup_text;
	// Background
	Background background(window);
	// Powerups
	Powerup power;
	// ImGui fun
	ImGuiStuff imgui_window(window);
	bool settings = false;
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
			imgui_window.loop(power, dif, powerup, level, world, window, barrier, p1, bricks, b1, background);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F12))
		{
			settings = false;
		}
		b1.checkCollision(p1, false, false);
		// fixes the bug of the ball endlessly bouncing wall to wall and now adds an elments of complexity
		b1.checkCollision(barrier.barriers[1], true, false);
		b1.checkCollision(barrier.barriers[3], true, true);
		for (long unsigned int i = 0; i < bricks.size(); i++)
		{
			if (b1.checkCollision(bricks[i]))
			{
				ball.play_ball();
				world.DestroyBody(bricks[i].body);
				bricks.erase(bricks.begin() + i);
				powerup++;
				if (powerup % 5 == 0)
				{
					power.reset(world, window, dif, p1, b1);
					power.select_powerup(world, dif, window.getSize().x / 30, b1, p1);
				}
			}
		}
		// Brick loop
		window.clear();
		world.Step(1.0 / 60, int32(8), int32(3));
		background.update(window);
		text.update_text(window, sf::Vector2f(10, window.getSize().y * 0.9), "Score " + std::to_string(powerup) + " Level " + std::to_string(level)); // Text for score
		pwrup_text.update_text(window, sf::Vector2f(window.getSize().x * 0.8, window.getSize().y * 0.9), power.words);
		if (bricks.empty())
		{
			bricks[0].refill_vector(world, window, dif, bricks);
			level++; // Do someting with the level system
		}
		if (b1.deathCollision(world, window, barrier.barriers[0], powerup, b1, p1, bricks, dif))
		{
			power.words = "";
			power.reset(world, window, dif, p1, b1);
		}
		p1.updatePosition(window);
		b1.updatePosition(window);
		// for (long unsigned int i = 0; i < bricks.size(); i++)
		// {
		// 	if (b1.checkCollision(bricks[i]))
		// 	{
		// 		ball.play_ball();
		// 		world.DestroyBody(bricks[i].body);
		// 		bricks.erase(bricks.begin() + i);
		// 		powerup++;
		// 		if (powerup % 5 == 0)
		// 		{
		// 			power.reset(world, window, dif, p1, b1);
		// 			power.select_powerup(world, dif, window.getSize().x / 30, b1, p1);
		// 		}
		// 	}
		// }
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