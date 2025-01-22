//Lewis Andrew Broad. Buckinghamshire New University
#pragma once
#include "Character.h"

enum class Specialty {
	Knight,
	Mage,
	Rogue,
	Wimp,
};

class Player : public Character
{
private:
	Specialty specialty;


public:
	Player(string name,Specialty specialty,int maxHealth, int health, int physDamage, int magDamage, int armour, int magResist) :Character(name,maxHealth, health, physDamage, magDamage, armour, magResist) {
	}
	void Display() const override;
	static string getSpecialty(Specialty specialty);

	static Player* PlayerCreation();

	void levelUp() override;

	void heal(int healing);
	void boostAttack(int boost);
	void resistBoost(int boost);
	bool playerCreated = false;
};