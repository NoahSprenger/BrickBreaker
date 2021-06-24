#ifndef IMGUISTUFF_H
#define IMGUISTUFF_H
#include "Background.cpp"
#include "Ball.cpp"
#include "Barriers.cpp"
#include "Brick.cpp"
#include "Paddle.cpp"
#include "Powerup.cpp"
#include "Text.cpp"
#include <SFML/Graphics.hpp>
#include <imgui/imgui-SFML.h>
#include <imgui/imgui.h>

struct ImGuiStuff
{
	ImGuiStuff(sf::RenderWindow& window, int dif)
	{
		ImGui::SFML::Init(window);
		selectedItem = dif;
	}
	// Loop for the imgui window
	void loop(Powerup& power, int& dif, int& powerup, b2World& world, sf::RenderWindow& window, Barriers& barrier, Paddle& p1, std::vector<Brick>& bricks, Ball& b1, Background& background)
	{
		static const char* itemsen[] { "Easy", "Normal", "Hard" };
		static const char* itemsfr[] { "Facile", "Normal", "Difficile" };
		if (english)
		{
			ImGui::Begin("Settings");
			ImGui::TextWrapped("HOW TO PLAY BRICK BREAKER.\n1-> 'A' to move the paddle to the left.\n2-> 'D' to move the paddle to the right.\n3-> Aim for the bricks using the paddle. The right side of the paddle sends the ball to the right and vice versa for the left side.\n4-> When the ball hits the walls it will bounce downwards at a 45 degree angle.\n5-> Clear all the bricks for a suprise.\n6-> Hit the star for a power up");
			if (ImGui::ListBox("Difficulty", &selectedItem, itemsen, IM_ARRAYSIZE(itemsen)))
			{
				dif = selectedItem + 1; // Used because the array starts at one but I need the dif to be a value from 1-3
			}
			if (ImGui::Button("Fullscreen - this will reset progress"))
			{
				window.close();
				window.create(sf::VideoMode(1920.0f, 1080.0f), "Brick Breaker", sf::Style::Fullscreen);
				window.setVerticalSyncEnabled(true);
				// Resize barrier
				barrier.resize(world, window);
				// Resize paddle
				p1.resize(world, window);
				// Reset text
				power.words = "";
				// Resize ball
				b1.resize(world, window, dif, p1);
				// Resize background
				background.resize(window);
				// Redo bricks
				bricks[0].empty_vector(world, bricks);
				bricks[0].refill_vector(world, window, dif, bricks);
				// Reset counters
				powerup = 0;
			}
			if (ImGui::Button("Default - this will reset progress"))
			{
				window.close();
				window.create(sf::VideoMode(1200.0f, 675.0f), "Brick Breaker", sf::Style::Default);
				window.setVerticalSyncEnabled(true);
				// Resize barrier
				barrier.resize(world, window);
				// Resize paddle
				p1.resize(world, window);
				// Reset text
				power.words = "";
				// Resize ball
				b1.resize(world, window, dif, p1);
				// Resize background
				background.resize(window);
				// Redo bricks
				bricks[0].empty_vector(world, bricks);
				bricks[0].refill_vector(world, window, dif, bricks);
				// Reset counters
				powerup = 0;
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
			ImGui::TextWrapped("COMMENT JOUER À BRICK BREAKER.\n1-> 'A' Pour bouger la raquette vers la gauche.\n2-> 'D' Pour bouger la raquette vers la droite.\n3-> Vous visez pour les briques avec la balle lorsqu'elle rebondit sur la raquette. Lorsque la balle est sur la partie droite de la raquette, elle rebondit vers la droite et même pour la partie gauche.\n4-> Lorsque la balle frappe le mur, elle rebondit vers le bas à un angle de 45 degrés.\n5-> Effacez toutes les briques pour une surprise.\n6-> Frapper l'étoile pour une mise sous tension.");
			if (ImGui::ListBox("Difficulté", &selectedItem, itemsfr, IM_ARRAYSIZE(itemsfr)))
			{
				dif = selectedItem + 1;
			}
			if (ImGui::Button("Plein écran - cette action va réinitialiser la progression"))
			{
				window.close();
				window.create(sf::VideoMode(1920.0f, 1080.0f), "Brick Breaker", sf::Style::Fullscreen);
				window.setVerticalSyncEnabled(true);
				// Resize barrier
				barrier.resize(world, window);
				// Resize paddle
				p1.resize(world, window);
				// Reset text
				power.words = "";
				// Resize ball
				b1.resize(world, window, dif, p1);
				// Resize background
				background.resize(window);
				// Redo bricks
				bricks[0].empty_vector(world, bricks);
				bricks[0].refill_vector(world, window, dif, bricks);
				// Reset counters
				powerup = 0;
			}
			if (ImGui::Button("Défaut - cette action va réinitialiser la progression"))
			{
				window.close();
				window.create(sf::VideoMode(1200.0f, 675.0f), "Brick Breaker", sf::Style::Default);
				window.setVerticalSyncEnabled(true);
				// Resize barrier
				barrier.resize(world, window);
				// Resize paddle
				p1.resize(world, window);
				// Reset text
				power.words = "";
				// Resize ball
				b1.resize(world, window, dif, p1);
				// Resize background
				background.resize(window);
				// Redo bricks
				bricks[0].empty_vector(world, bricks);
				bricks[0].refill_vector(world, window, dif, bricks);
				// Reset counters
				powerup = 0;
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
	int selectedItem = 0;
	bool english = true;
};

#endif