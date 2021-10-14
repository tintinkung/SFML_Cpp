#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include <string>
#include <json/json.h>
#include <json/value.h>
#include <fstream>


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

		float moveSpeed;

		//damage of this enemy when reached over point
		unsigned int hitDamage;
		unsigned short int type;

		Json::Value rootData;
		Json::Value typeData;

		// Json::Value typeData;

		void _setVariable(unsigned int points, unsigned short int health, unsigned int hitDamage, float size, float moveSpeed, sf::Color bodyColor, sf::Color borderColor);
		const sf::Color _readColorFromData(Json::Value data, int type, std::string colorLabel) const;

	public:
		// --- Constructors ---
		Enemy(unsigned short int type);
		Enemy();

		// --- Destructors ---
		~Enemy();

		// --- Accessors ---
		const unsigned int& getPoint() const { return this->points; }
		const float& getSize() const { return this->size; }
		const unsigned short int& getHealth() const { return this->health; }
		const unsigned int& getHitDamage() const { return this->hitDamage;  }
		const unsigned short int& getType() const { return this->type;  }
		const float& getMoveSpeed() const { return this->moveSpeed;  }
		const sf::Color& getBodyColor() const { return this->borderColor;  }
		const sf::Color& getBorderColor() const { return this->borderColor; }

		// --- Modifiers ---
		void setHealth(unsigned short int& value) { this->health = value; }
		void setType(unsigned short int& type) { this->type = type; initType(this->type); }
		void setSize(float& value) { this->size = value; }

		// --- Functions ---
		void initValiables();
		void initType(int type);
		static int getTypeMember();
		void initJsonData();
};

#endif // !ENEMY_HPP
