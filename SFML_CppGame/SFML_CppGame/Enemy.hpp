#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <iostream>


class Enemy
{
private:
	// point worth of this enemy when killed
	unsigned int points;

	// click health - how many time player needed to click to get this enemy killed
	unsigned short int health; // later

	sf::Color bodyColor;

	sf::Color borderColor;

	float size;

	//damage of this enemy when reached over point
	unsigned int hitDamage;
	unsigned short int type;

	void setVariablePrivate(unsigned int points, 
		unsigned short int health, 
		sf::Color bodyColor, 
		sf::Color borderColor, 
		unsigned int hitDamage,
		float size);

public:
	// --- Constructors ---
	Enemy(unsigned short int type);
	Enemy();

	// --- Destructors ---
	~Enemy();

	// --- Accessors ---
	const unsigned int getPoint() const { return this->points; }
	const float getSize() const { return this->size; }
	const unsigned short int getHealth() const { return this->health; }
	const unsigned int getHitDamage() const { return this->hitDamage;  }
	const unsigned short int getType() const { return this->type;  }
	const sf::Color getBodyColor() const { return this->borderColor;  }
	const sf::Color getBorderColor() const { return this->borderColor; }

	// --- Modifiers ---
	void setHealth(unsigned short int value) { this->health = value; }
	void setType(unsigned short int type) { this->type = type; initType(this->type); }
	void setSize(float value) { this->size = value; }

	// --- Functions ---
	void initValiables();
	void initType(unsigned short int type);
	static int getTypeMember();
};

#endif // !ENEMY_HPP
