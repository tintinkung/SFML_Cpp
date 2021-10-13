#include "Game.h"

#pragma region Initializations

/// <summary>
/// {Private function}
/// </summary>
void Game::initializeVariables()
{
	this->window = nullptr;

// --- Game Logic ---
    this->gameEnded = false;
    this->points = 0;
    this->health = 10;
    this->enemySpawnTimerMax = 50.0f;
        //start timer at mac value then it returns to 0
    this->enemySpawnTimer = this->enemySpawnTimerMax; 
    this->enemiesSpeed = 10.0f;
    this->maxEnemies = 5;
    this->mouseHelds = false; // mouse first click should be registered
}

void Game::initWindow()
{
	// give window with title bar in 800px*600px  + Close button(close window)
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	
	this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
    if(!this->font_SansMono.loadFromFile("../Assets/Fonts/Noto_Sans_Mono/NotoSansMono.ttf"))
    {   // LOG ERROR CANNOT LOAD FONT
        std::cout << "ERROR: Game::initFonts() \n"
            << "AT: sf::Font::loadFromFile(\"../Assets/Fonts/Noto_Sans_Mono/NotoSansMono.ttf\")"
            << std::endl;
        this->hasFont = false;
    }
    else this->hasFont = true;
}

void Game::initTexts()
{
    if(hasFont) this->uiText.setFont(this->font_SansMono);
    this->uiText.setCharacterSize(12);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NULL");
}

void Game::initEnemies()
{
    #pragma region Set Enemy position
    this->enemyObject.setPosition(10.0f, 10.0f);
    this->enemyObject.setSize(sf::Vector2f(50.0f, 50.0f));
    this->enemyObject.setScale(sf::Vector2f(1.0f, 1.0f));
    this->enemyObject.setFillColor(sf::Color::Cyan);
    this->enemyObject.setOutlineColor(sf::Color::Green);
    this->enemyObject.setOutlineThickness(1.0f);
    #pragma endregion
}

#pragma endregion

#pragma region Constructors & Destructors

Game::Game()
{
	this->initializeVariables();
    this->initWindow();
    this->initFonts();
    this->initTexts();
    this->initEnemies(); 
}

Game::~Game()
{
    // elased the window
	delete this->window;
}

#pragma endregion

const bool Game::running() const
{   // return window is open
	return this->window->isOpen();
}

const bool Game::gameIsEnded() const
{
    return this->gameEnded;
}

void Game::update()
{
    this->pollEvents();

    if(!gameEnded) //as long as game not ended, do nothing(for now)
    {
        this->updateMousePositions();

        this->updateText();

        this->updateEnemies();
    }

    if (this->health <= 0)
    {   // Game Ended conditions.
        this->gameEnded = true;
    }

    // --- update mouse positions ---

    /* --- Relative to screen ---
     *  std::cout << "Mous pos: " << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << std::endl;
     */

    /* --- Relative to window ---
     * std::cout << "Mouse pos: " 
     *  << sf::Mouse::getPosition(*this->window).x << " " 
     *  << sf::Mouse::getPosition(*this->window).y << std::endl;
     */
   
}


/// <summary>
/// Render the game windows <br/>
/// - clear old frame <br/>
/// - render objects <br/>
/// - display frame in window
/// </summary>
/// <returns>{void}</returns>
void Game::render()
{
    // --- clear window ---
    this->window->clear(/*sf::Color(255, 0, 0, 255)*/);
    // --------------------

#pragma region Main Render Loop, ALL rendering goes here

    this->renderEnemies(*this->window);


    
    this->renderText(*this->window);
#pragma endregion

    // --- Draw game objects ---
    this->window->display();
    // -------------------------
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

/// <summary>
/// Update the mous positions:
/// - Mouse position relative to the game window(Vector2i)
/// </summary>
/// <returns>{void}</returns>
void Game::updateMousePositions()
{
    // update both view coord and window coord for more use case
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);

    /** mapPixelToCoords();
     *  - take our mouse position from window, map it from pixel to window x,y coords
     */
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::setEnemy(Enemy enemyType)
{
    this->enemyObject.setScale(sf::Vector2f(enemyType.getSize(), enemyType.getSize()));
    this->enemyObject.setFillColor(enemyType.getBodyColor());
    this->enemyObject.setOutlineColor(enemyType.getBorderColor());
}

/// <summary>
/// spawn enemies in.
/// spawn enemies and set their colors and positions:
/// - set a random positions.
/// - set a random color.
/// - add enemy to the vector.
/// </summary>
void Game::spawnEnemy()
{
    this->enemyObject.setPosition (
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemyObject.getSize().x)),
        0.0f
    );

    // Randomize emeny type
    int type = rand() % 5;
    Enemy enemyType(type + 1);

    setEnemy(enemyType);

    // Spawn the enemy
    this->enemies.push_back(this->enemyObject);
}

/// <summary>
/// updated the enemy spawn timer and spawns enemies.
/// when total amout of enemies is smaller than the maximum.
/// then Move the enemies down wards.
/// then Remove the enemy at the edge of the screen(TODO).
/// </summary>
void Game::updateEnemies()
{
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            this->spawnEnemy();
            this->enemySpawnTimer = 0.0f;
        }
        else
            this->enemySpawnTimer += 1.0f;
    }

    // move() all the enemy downwards.
    for (int i = 0; i < this->enemies.size(); i++)
    {
        bool deleted = false;

        this->enemies[i].move(0.0f, this->enemiesSpeed);

        // Check if enemy passes bottom of the screen (obliterate it)
        if (this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);

            this->health -= 1;
        }
    }

    // Check if Clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left/*mouse left click*/))
    {
        if (this->mouseHelds == false)
        {
            this->mouseHelds = true;
            bool deleted = false;
            for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
            {
                /** .getGlobalBounds()
                 *  - get bounds of enemy (enemy is rectangle)
                 */
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                {
                    // Gain Points
                    if (this->enemies[i].getFillColor() == sf::Color::Magenta)
                        this->points += 10;
                    else if (this->enemies[i].getFillColor() == sf::Color::Blue)
                        this->points += 7;
                    else if(this->enemies[i].getFillColor() == sf::Color::Red)
                        this->points += 5;
                    else if(this->enemies[i].getFillColor() == (sf::Color::Red + sf::Color::Yellow))
                        this->points += 3;
                    else if(this->enemies[i].getFillColor() == sf::Color::Yellow)
                        this->points += 2;
                    else if(this->enemies[i].getFillColor() == sf::Color::Green)
                        this->points += 1;

                    // Delete the enemy
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                }
            }
        }
    }
    else
    {
        this->mouseHelds = false;
    }



    std::stringstream ss; ss 
        << "Enemy Spawn Delay: " << this->enemySpawnTimerMax - enemySpawnTimer
        << "  |  Points: " << this->points
        << "  |  Healths: " << this->health;

    std::cout << ss.str() << "   \r"; // DEBUGGING ONLY
}

void Game::renderEnemies(sf::RenderTarget& target)
{
    for (auto &e : this->enemies)  //make for loop much faster
    {
        target.draw(e);
    }
}

void Game::renderText(sf::RenderTarget& target)
{
    target.draw(this->uiText);
}

void Game::updateText()
{
    std::stringstream ss; ss 
        << "Points: " << this->points << "\n"
        << "Healths: " << this->health;
    this->uiText.setString(ss.str());
}


