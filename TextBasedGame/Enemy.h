#pragma once
#include "Character.h"
class Enemy : public Character
{
private:
	string type;
public:
	Enemy(string name, string type, int maxHealth, int health, int physDamage, int magDamage, int armour, int magResist, int level = 1) :
		Character(name, maxHealth, health, physDamage ,magDamage, armour, magResist, level), type(type) {

	}
	void Display() const override;

};

class Goblin :public Enemy
{
public:
	Goblin(string name, int level) :
		Enemy(name, "Goblin", 20 + 5 * level,20 +5 *level, 5 + 5 * level, 3 + 3 * level, 3 + level, 3 + level, level) {}
};

class EnemyTank :public Enemy
{
public:
	EnemyTank(string name, int level) :
		Enemy(name, "Magic Tree", 50 + 5 * level, 50 + 5 * level, 3 + 3 * level, 4 + 4 * level, 6 + 2 * level, 6 + 2 * level, level) {}

};

class Gnome :public Enemy 
{
public:
	Gnome(string name, int level) :
		Enemy(name, "Evil Magic Gnome", 10, 10, 3 + 2 * level, 20 + 5 * level, 3 + 1 * level, 20 + 2 * level, level) {}
};		