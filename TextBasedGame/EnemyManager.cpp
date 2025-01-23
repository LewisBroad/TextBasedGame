//Lewis Andrew Broad. Buckinghamshire New University
#include "EnemyManager.h"

//function to create a random enemy
Enemy*  EnemyManager::createEnemy(int playerLevel) {
	int randNum = rand() % 2; //increse number if more enemies are created
	if (randNum == 0) {
		return new Goblin("Goblin", playerLevel); //spawn goblin
	}
	else {
		return new EnemyTank("Magic Tree", playerLevel); //spawn tank
	}
}