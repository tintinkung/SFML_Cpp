#include "Enemy.hpp"

void Enemy::_setVariable(unsigned int points, unsigned short int health, unsigned int hitDamage, float size, float moveSpeed, sf::Color bodyColor, sf::Color borderColor)
{
	this->points = points;
	this->bodyColor = bodyColor;
	this->borderColor = borderColor;
	this->health = health;
	this->hitDamage = hitDamage;
	this->size = size;
	this->moveSpeed = moveSpeed;
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
	initJsonData();
	initValiables();
}

Enemy::~Enemy()
{
	// delete this;
}

void Enemy::initValiables()
{
	//set default variables
	_setVariable(10, 1, 10, 1.0f, 10.0f, sf::Color::White, sf::Color::White);
}

void Enemy::initType(int type)
{
	bool typeValid = false;

	// Iterate over the sequence elements.
	for (int i = 0; i < this->typeData.size(); ++i)
	{
		//check if input type match the json	
		if (type == this->typeData[i].get("type", -1).asInt())
		{
			_setVariable(
				this->typeData[i].get("points", -1).asUInt(),
				this->typeData[i].get("health", -1).asUInt(),
				this->typeData[i].get("hitDamage", -1).asUInt(),
				std::stof(this->typeData[i].get("size", 1.0f).asString()),
				std::stof(this->typeData[i].get("moveSpeed", 1.0f).asString()),
				_readColorFromData(this->typeData, i, "bodyColor"),
				_readColorFromData(this->typeData, i, "borderColor")
			);

			typeValid = true;
		}
	}

	if (!typeValid)
	{
		_setVariable(-1, -1, -1, 1, 1.0f, sf::Color{ 0xFF0000FF }, sf::Color{ 0xFF0000FF });
		std::cout << "ERROR: Enemy type is invalid (" << type << ")" << std::endl;
	}

	
	// https://www.webfx.com/web-design/color-picker/
}

int Enemy::getTypeMember()
{
	// MUST UPDATE THIS MANUALLY
	return 10;
}

const sf::Color Enemy::_readColorFromData(Json::Value data, int type, std::string colorLabel) const
{
	const int R = data[type][colorLabel]["rgba"][0].asInt();
	const int G = data[type][colorLabel]["rgba"][1].asInt();
	const int B = data[type][colorLabel]["rgba"][2].asInt();
	const int A = data[type][colorLabel]["rgba"][3].asInt();

	return sf::Color(R, G, B, A);
}

void Enemy::initJsonData()
{
	//read the enemy types data
	std::ifstream enemyType_file("../data/EnemyType.json", std::ifstream::binary);
	enemyType_file >> this->rootData; //push json file to root data

	this->typeData = this->rootData["EnemyType"]/*[type index]*/;
}