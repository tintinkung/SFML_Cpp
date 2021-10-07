#include "Game.h"

/// <summary>
/// {Private function}
/// </summary>
void Game::initializeVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	// give window with title bar in 800px*600px  + Close button(close window)
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	
	this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);
}

/// <summary>
/// Constructors / Destructors
/// </summary>
Game::Game()
{
	this->initializeVariables();
	this->initWindow();
}

Game::~Game()
{
    // elased the window
	delete this->window;
}

/// <summary>
/// Accessors
/// </summary>
/// <returns>Window is open</returns>
const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::update()
{
    this->pollEvents();
}


/// <summary>
/// Render the game windows
/// </summary>
/// <returns>{void}</returns>
void Game::render()
{
    /*
     * @return void
     * 
     * - clear old frame
     * - render ovjects
     * - display frame in window
     * 
     * Render the game windows
     */
    this->window->clear(sf::Color(255, 0, 0, 255));
    
    //Draw game objects
    this->window->display();
}

void Game::pollEvents()
{
    // --- Event polling ---
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
            //when we click the close button, it send event with type close
        case sf::Event::Closed:
            this->window->close();
            break;

            //Track esc key when pressed.
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
                this->window->close(); //close window using esc key
            break;     
        }
    }
}


