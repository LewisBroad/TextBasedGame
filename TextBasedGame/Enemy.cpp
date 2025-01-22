//Lewis Andrew Broad. Buckinghamshire New University
#include "Enemy.h"

void Enemy::Display()const{
	cout << "\nEnemy Info:\n";
	Character::Display();
	cout << "Enemy Type: " << type << endl;
}