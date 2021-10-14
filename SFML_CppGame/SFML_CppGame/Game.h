#ifndef GAME_H
#define GAME_H

// pre compile header ( pre include heavy file )
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <sstream>
#include "Enemy.hpp"

#include <json\json.h>
#include <json\value.h>
#include <fstream>

// ../SFML_CppGame/data/EnemyType.json

/// <summary>
/// Class that acts as the game engine.
/// (Wrapper Class)
/// </summary>
class Game 
{
	private:
	// ==== Variables ====
		// --- Window ---
		sf::RenderWindow* window;
		sf::Event ev;
		sf::VideoMode videoMode;

	// --- Mouse Positions ---
		sf::Vector2i mousePosWindow;
		sf::Vector2f mousePosView;

	// ==== Assets ====
		// --- FONTS ---
		sf::Font font_SansMono;
		bool hasFont;

		// --- Text ---
		sf::Text uiText;

	// --- Game Logic ---
		bool gameEnded;
		unsigned points;
		int health;
		float enemySpawnTimer;
		float enemySpawnTimerMax;
		float enemiesSpeed;
		int maxEnemies; // max Enemies on the screen
		bool mouseHelds;


	// --- Game Objects ---
		
		struct RenderEnemy 
		{
			sf::RectangleShape enemyObject;
			// std::vector<sf::RectangleShape> enemies;
			Enemy enemyData;
		};
		RenderEnemy enemy;
	    std::vector<RenderEnemy> enemies;

	// --- Private functions ---
		void initializeVariables();
		void initWindow();
		void initFonts();
		void initTexts();
		void initEnemies();
		
	public:
	// --- Constructor ---
		Game();

	// --- Destructors ---
		virtual ~Game();

	// --- Accessors ---
		const bool running() const;
		const bool gameIsEnded() const;

	// --- Functions ---
		void pollEvents();

		void updateMousePositions();
		
		void spawnEnemy();
		void updateEnemies();
		void renderEnemies(sf::RenderTarget& target);
		//not rendering on the main window(default render target)
		void renderText(sf::RenderTarget& target);
		void updateText();
		void setEnemy(unsigned short int enemyType);
		void update();
		void render();
};

#endif // !GAME_H
