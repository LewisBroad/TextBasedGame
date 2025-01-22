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
	/*void takeDamage(int damageTaken) {
		health -= damageTaken;
		if (health < 0) health = 0;
		cout << name << " has taken " << damageTaken << " damage\n" << "Remaining HP: " << health << endl;
	}*/

	/*virtual int attack()const {
		if (physDamage > magDamage) {
			cout << name << " attacks for " << physDamage << endl;
			int  damage = 
			return damage;
		}
	}*/

	bool isAlive() const {
		return health > 0;
	}

	void gainXP(int xpGain) {
		exp += xpGain;
		cout << xpGain << " XP Gained\n";
		canLevelUp();
		
	}

	void canLevelUp() {
		while (exp >= levelXp) {
			exp -= levelXp;
			level++;
			levelXp = 100 * level / 2;
			levelUp();
		}
	}
	virtual void levelUp() {
	
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

	int getLevel() const { return level; }
	string getName() const { return name; }
protected:
	//double damage;
	//double HP;


};

//void Character::newGame() {
//	level = 1;
//	money = 0;
//	HP = 100;
//	CharacterCreation();
//}


//string Character::CharacterCreation() {
//	char ch;
//	cout << "Please name your character : \n" << endl;
//	cin >> name;
//	cout << "\n You are called " << name << ". correct?\n" << endl << "Y for yes, N for no." << endl;
//	getc(stdin);
//	cin.get(ch);
//	while (ch == 'n' || ch == 'N') {
//		cin.clear();
//		cout << "Please name your character : \n" << endl;
//		cin >> name;
//		cout << "\n You are called " << name << ". correct?\n" << endl << "Y for yes, N for no." << endl;
//		getc(stdin);
//		cin.get(ch);
//	}
//	return name;
//}

//void Character::gainXP(int xp) {
//	this->XP += xp;
//	if (this->XP >= 100) {
//		this->XP -= 100;
//		this->level++;
//	}
//}
//void Character::stats(int strength, int intelect, int swiftness) {
//	
//}
