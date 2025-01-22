//Lewis Andrew Broad. Buckinghamshire New University
#pragma once
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;


class Character {
protected:
	string name;
	int level;
	int maxHealth;
	int health;
	int armour;
	int magResist;
	int physDamage;
	int magDamage;
	int exp;
	int levelXp;

public:
//	void newGame();
	Character(string name, int maxHealth, int health, int physDamage, int magDamage, int armour, int magResist, int level = 1) :
		name(name),maxHealth(maxHealth), health(health), physDamage(physDamage),magDamage(magDamage),
		armour(armour),magResist(magResist), level(level), exp(0) 
	{
		levelXp = 100 * level/2;
	}
	friend class GameManager; // this allows the gamemanager to access the private members of the character class

	virtual void Display()const {
		cout << "Name: " << name << endl
			<< "HP: " << health << "/"<< maxHealth << endl
			<< "Armour: " << armour << endl
			<< "Magic Resist: " << magResist << endl
			<< "Physical Damage: " << physDamage << endl
			<< "Magic Damage: " << magDamage << endl
			<< "Level: " << level << endl
			<< "XP: " << exp << "/" << levelXp << endl;
	}
	void takePhysicalDamage(int damage) {
		int damageReduction = damage - armour;
		if (damageReduction <= 0) damageReduction = 1;
		health -= damageReduction;
		if (health < 0) health = 0;
		cout << name << " takes " << damageReduction << " physical damage.\n";
	}
	void takeMagicDamage(int damage) {
		int damageReduction = damage - magResist;
		if (damageReduction <= 0) damageReduction = 1;
		health -= damageReduction;
		if (health < 0) health = 0;
		cout << name << " takes " << damageReduction << " magic damage.\n";
	}
private:
	//polymorphic functions. Each instance has their own return of this function.
	virtual int physicalAttack()const {
		return physDamage;
	}
	virtual int magicAttack() const {
		return magDamage;
	}
	virtual int getHealth() const {
		return health;
	}
	virtual int getPhysicalResist() const{
		return armour;
	}
	virtual int getMagicResist()const {
		return magResist;
	}
	void gainXP(int xpGain) { //takes in an int value and adds it to the exp value
		exp += xpGain;
		cout << xpGain << " XP Gained\n";
		canLevelUp();

	}
public:
	void canLevelUp() {
		while (exp >= levelXp) { //checks to see the characters current xp is greater than the xp needed to level up
			exp -= levelXp;
			level++;
			levelXp = 100 * level / 2;
			levelUp();
		}
	}
	virtual void levelUp() { //function to level up the character

		cout << name << " is now level " << level << endl;
		maxHealth += 10;
		health = maxHealth;
		cout << "Health grown to " << health << endl;
		if (magDamage > physDamage) {
			magDamage += 5;
			physDamage += 2;
		}
		else {
			physDamage += 5;
			magDamage += 2;
		}

		cout << "Physical damage grown to " << physDamage << endl;
		cout << "Magic damage grown to " << magDamage << endl;

	}
	bool isAlive() const {
		return health > 0;
	}
	int getLevel() const { return level; }
	string getName() const { return name; }
};
