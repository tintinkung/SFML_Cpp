#include "Enemy.hpp"

void Enemy::setVariablePrivate(
	unsigned int points, 
	unsigned short int health, 
	sf::Color bodyColor, 
	sf::Color borderColor, 
	unsigned int hitDamage,
	float size)
{
	this->points = points;
	this->bodyColor = bodyColor;
	this->borderColor = borderColor;
	this->health = health;
	this->hitDamage = hitDamage;
	this->size = size;
}

Enemy::Enemy(unsigned short int type)
{
	//MUST BE IN THIS ORDER
	this->type = type;
	initValiables();
	initType(this->type);
	
}

Enemy::Enemy()
{
	initValiables();
}

Enemy::~Enemy()
{
	// delete this;
}

void Enemy::initValiables()
{
	//set default variables
	setVariablePrivate(10, 1, sf::Color::White, sf::Color::White, 10, 1.0f);
}

void Enemy::initType(unsigned short int type)
{
	switch(type)
	{   // https://www.webfx.com/web-design/color-picker/
		case 1:
			setVariablePrivate(3, 1, sf::Color::Green, sf::Color::Green, 10, 2.0f);
			break;
		case 2:
			setVariablePrivate(5, 1, sf::Color(38, 255, 31), sf::Color(136, 255, 31), 10, 1.7f);
			break;
		case 3:
			setVariablePrivate(7, 1, sf::Color(230, 233, 26), sf::Color(233, 190, 26), 10, 1.5f);
			break;
		case 4:
			setVariablePrivate(9, 1, sf::Color(233, 190, 26), sf::Color(233, 141, 26), 10, 1.3f);
			break;
		case 5:
			setVariablePrivate(11, 1, sf::Color(233, 141, 26), sf::Color(233, 26, 26), 10, 1.0f);
			break;

	default:
		setVariablePrivate(10, 1, sf::Color{ 0xFF0000FF }, sf::Color{ 0xFF0000FF }, 10, 1.0f);
		std::cout << "Enemy type is valid ("<< type << ")" << std::endl;
		break;
	}
}
