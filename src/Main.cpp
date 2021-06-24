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
#include <imgui/imgui-SFML.h>
#include <imgui/imgui.h>
#include <vector>

int main()
{
#if defined(_DEBUG)
	std::cout << "Debugging!" << std::endl; // For my Makefile environment
#endif
	std::vector<Brick> bricks;
	b2World world(b2Vec2(0.0, 0.0)); // Box2d world for physics
	Menu menu;
	int dif = menu.Run_Menu(); // Saves the difficulty to a variable
	sf::RenderWindow window;
	window.create(sf::VideoMode(1200.0f, 675.0f), "Brick Breaker", sf::Style::Default); // Creates SFML window for rendering
	bricks[0].refill_vector(world, window, dif, bricks);
	window.setVerticalSyncEnabled(true); // Attempts to combat screen tearing (in tests more effective than window.setFrameRateLimit())
	// Brick for powerups
	Brick target(world, -100, -100, 30, 30); // Rendered off screen
	sf::Texture star;
	star.loadFromFile("content/star.png");
	target.setTexture(&star);
	// From Barriers.cpp
	Barriers barrier(world, window);
	// From Ball.cpp
	Ball b1(world, window.getSize().x / 2, 300, 20, 250 * dif, 90, true); // Main ball
	// From Paddle.cpp
	Paddle p1(world, window.getSize().x / 2 - 50, window.getSize().y * 0.9, 100, 10); // Paddle
	// Sound stuff
	Sounds ball;	  // For sounds and music
	ball.play_main(); // Starts playing main music on idependant thread
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
	ImGuiStuff imgui_window(window, dif); // Initialize the object so the loop() function can be called
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
		// For opening the imgui window
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11) || settings)
		{
			settings = true;
			imgui_window.loop(power, dif, powerup, world, window, barrier, p1, bricks, b1, background);
		}
		// For closeing the imgui window
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F12))
		{
			settings = false;
		}
		// Checks if the main ball hits the paddle
		if (b1.checkCollision(p1, false, false))
		{
			ball.play_ball(); // Plays the ball sound
		}
		// fixes the bug of the ball endlessly bouncing wall to wall and now adds an element of complexity
		// Checks to see if the ball hits the walls
		if (b1.checkCollision(barrier.barriers[1], true, false))
		{
			ball.play_ball();
		}
		if (b1.checkCollision(barrier.barriers[3], true, true))
		{
			ball.play_ball();
		}
		// Checks to see if the ball hits any bricks
		for (long unsigned int i = 0; i < bricks.size(); i++)
		{
			if (b1.checkCollision(bricks[i]))
			{
				ball.play_ball();
				world.DestroyBody(bricks[i].body); // Deletes the brick from the box2d world
				bricks.erase(bricks.begin() + i);  // Deletes the brick from the vector
				powerup++;
				if (powerup % 5 == 0)
				{
					target.reset(world, window); // Reset the powerup star
					power.words = "";
					power.reset(world, window, dif, p1, b1); // Reset the powerup
				}
			}
		}
		// Checks to see if the target is hit
		if (b1.checkCollision(target))
		{
			ball.play_ball();
			target.resetPosition(sf::Vector2f(-100, -100));
			power.reset(world, window, dif, p1, b1);
			power.select_powerup(world, dif, window.getSize().x / 30, b1, p1); // Selects a new powerup
		}
		// Brick loop
		window.clear();
		world.Step(1.0 / 60, int32(8), int32(3));
		background.update(window);
		text.update_text(window, sf::Vector2f(10, window.getSize().y * 0.9), "Score " + std::to_string(powerup) + " Level " + std::to_string(level)); // Text for score and level
		pwrup_text.update_text(window, sf::Vector2f(window.getSize().x * 0.8, window.getSize().y * 0.9), power.words);								  // Update the powerup text
		if (bricks.empty())
		{
			bricks[0].refill_vector(world, window, dif, bricks); // Refill the bricks
			level++;											 // Move the level up one
			if (level > 4)
			{
				level = 1; // Only 4 levels so resets for the background to go back to the normal loop
			}
			background.new_background(level); // Changes the background when the level changes
		}
		// first checks if the no death powerup is in play
		if (!b1.death)
		{
			// Checks to see if the ball hit the floor
			if (b1.deathCollision(world, window, barrier.barriers[0], powerup, b1, p1, bricks, dif))
			{
				power.words = "";
				power.reset(world, window, dif, p1, b1);
				target.resetPosition(sf::Vector2f(-100, -100));
			}
		}
		// Update object positions and draw them
		p1.updatePosition(window);
		b1.updatePosition(window);
		for (auto i : bricks)
		{ // I like this way
			i.updatePosition(window);
		}
		target.updatePosition(window);
		ImGui::SFML::Render(window);
		window.display();
	}
	ball.stop_main();		 // Stop music
	ImGui::SFML::Shutdown(); // Stop imgui
	return 0;
}