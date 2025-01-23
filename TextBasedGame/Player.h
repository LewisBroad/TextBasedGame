//Lewis Andrew Broad. Buckinghamshire New University
#pragma once
#include "Character.h"

enum class Specialty { //enum class for the player specialty
	Knight,
	Mage,
	Rogue,
	Wimp,
};

class Player : public Character //child class of character
{
private:
	Specialty specialty;


public:
	Player(string name,Specialty specialty,int maxHealth, int health, int physDamage, int magDamage, int armour, int magResist) :Character(name,maxHealth, health, physDamage, magDamage, armour, magResist) {
	} //constructor for the player class
	void Display() const override;
	void Display(bool breif) const override; //override for the display function.
	static string getSpecialty(Specialty specialty); // this converts the specialty enum to a string. static because it is not tied to an instance of the class

	static Player* PlayerCreation(); //Static  method that creates and returns a new Player object. it creates a new instance of the class

	void levelUp() override;

	void heal(int healing);
	void boostAttack(int boost);
	void resistBoost(int boost);
	bool playerCreated = false;
};