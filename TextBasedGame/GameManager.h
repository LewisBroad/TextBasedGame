//Lewis Andrew Broad. Buckinghamshire New University

#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Windows.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "ExceptionHandler.h"


using namespace std;


class GameManager
{
	string input;
	Player* player;

	// Define function pointers for the different attack types
	typedef void (GameManager::*AttackFunction)(Player* player, Enemy* enemy);

	//funtions for the players attacks.attacks
	void physicalAttack(Player* player, Enemy* enemy);
	void magicAttack(Player* player, Enemy* enemy);


public:
	GameManager();
	~GameManager();
	void startGame();
	void randomEncounters();
	void gameLoop();
	void magicGnome();
	//void gameLoop(Player& player);
	//void runGame();
protected:
	void Battle(Player *player, Enemy* enemy);
	void Shop();
	void Journey();

};

