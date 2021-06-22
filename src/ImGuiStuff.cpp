#ifndef IMGUISTUFF_H
#define IMGUISTUFF_H
#include "Background.cpp"
#include "Ball.cpp"
#include "Barriers.cpp"
#include "Brick.cpp"
#include "Paddle.cpp"
#include "Text.cpp"
#include <SFML/Graphics.hpp>
#include <imgui/imgui-SFML.h>
#include <imgui/imgui.h>

struct ImGuiStuff
{
	ImGuiStuff(sf::RenderWindow& window)
	{
		ImGui::SFML::Init(window);
	}
	void loop(int dif, int& powerup, int& level, b2World& world, sf::RenderWindow& window, Text& text, Barriers& barrier, Paddle& p1, std::vector<Brick>& bricks, Ball& b1, Background& background)
	{
		if (english)
		{
			ImGui::Begin("Settings");
			ImGui::TextWrapped("HOW TO PLAY BRICK BREAKER. 1-> 'A' to move the paddle to the left. 2-> 'D' to move the paddle to the right. 3-> Aim for the bricks using the paddle. The right side of the paddle sends the ball to the right and vice versa for the left side.");
			if (ImGui::Button("Fullscreen - this will reset progress"))
			{
				window.close();
				window.create(sf::VideoMode(1920.0f, 1080.0f), "Brick Breaker", sf::Style::Fullscreen);
				window.setVerticalSyncEnabled(true);
				// window.setFramerateLimit(60);
				barrier.resize(world, window);
				p1.resize(world, window);
				// Resize text
				text.resize(window);
				// Resize ball
				b1.resize(world, window, dif, p1);
				// Resize background
				background.resize(window);
				// Redo bricks
				bricks[0].empty_vector(world, bricks);
				bricks[0].refill_vector(world, window, dif, bricks);
				// Reset counters
				powerup = 0;
				level = 1;
			}
			if (ImGui::Button("Default - this will reset progress"))
			{
				window.close();
				window.create(sf::VideoMode(1200.0f, 675.0f), "Brick Breaker", sf::Style::Default);
				window.setVerticalSyncEnabled(true);
				// window.setFramerateLimit(60);
				barrier.resize(world, window);
				p1.resize(world, window);
				// Resize text
				text.resize(window);
				// Resize ball
				b1.resize(world, window, dif, p1);
				// Resize background
				background.resize(window);
				// Redo bricks
				bricks[0].empty_vector(world, bricks);
				bricks[0].refill_vector(world, window, dif, bricks);
				// Reset counters
				powerup = 0;
				level = 1;
			}
			if (ImGui::Button("French"))
			{
				english = false;
			}
			if (ImGui::Button("Quit"))
			{
				window.close();
			}
			ImGui::End();
		}
		else
		{
			ImGui::Begin("Paramètres");
			ImGui::TextWrapped("COMMENT JOUER À BRICK BREAKER. 1-> 'A' Pour déplacer la raquette vers la gauche. 2-> 'D' Pour déplacer la raquette vers la droite. 3-> Vous visez les briques avec la balle lorsqu'elle rebondit sur la raquette. Lorsque la balle est sur la partie droite de la raquette, elle rebondit vers la droite et vice versa pour la partie gauche.");
			if (ImGui::Button("Plein écran - cette action va réinitialiser la progression"))
			{
				window.close();
				window.create(sf::VideoMode(1920.0f, 1080.0f), "Brick Breaker", sf::Style::Fullscreen);
				window.setVerticalSyncEnabled(true);
				// window.setFramerateLimit(60);
				barrier.resize(world, window);
				p1.resize(world, window);
				// Resize text
				text.resize(window);
				// Resize ball
				b1.resize(world, window, dif, p1);
				// Resize background
				background.resize(window);
				// Redo bricks
				bricks[0].empty_vector(world, bricks);
				bricks[0].refill_vector(world, window, dif, bricks);
				// Reset counters
				powerup = 0;
				level = 1;
			}
			if (ImGui::Button("Défaut - cette action va réinitialiser la progression"))
			{
				window.close();
				window.create(sf::VideoMode(1200.0f, 675.0f), "Brick Breaker", sf::Style::Default);
				window.setVerticalSyncEnabled(true);
				// window.setFramerateLimit(60);
				barrier.resize(world, window);
				p1.resize(world, window);
				// Resize text
				text.resize(window);
				// Resize ball
				b1.resize(world, window, dif, p1);
				// Resize background
				background.resize(window);
				// Redo bricks
				bricks[0].empty_vector(world, bricks);
				bricks[0].refill_vector(world, window, dif, bricks);
				// Reset counters
				powerup = 0;
				level = 1;
			}
			if (ImGui::Button("Anglais"))
			{
				english = true;
			}
			if (ImGui::Button("Quitter"))
			{
				window.close();
			}
			ImGui::End();
		}
	}
	bool english = true;
};

#endif