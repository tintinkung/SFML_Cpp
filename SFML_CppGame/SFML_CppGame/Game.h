#pragma once

// pre compile header ( pre include heavy file )
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/// <summary>
/// Class that acts as the game engine.
/// (Wrapper Class)
/// </summary>
class Game
{
	private:
		// --- Variables ---
		// --- Window ---
		sf::RenderWindow* window;
		sf::Event ev;
		sf::VideoMode videoMode;

		//Private functions
		void initializeVariables();
		void initWindow();
		
	public:
		//Constructor / Destructors
		Game();
		virtual ~Game();

		//Accessors
		const bool running() const;

		//Functions
		void pollEvents();
		void update();
		void render();
};

