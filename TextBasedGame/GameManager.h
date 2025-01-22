//Lewis Andrew Broad. Buckinghamshire New University

#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Windows.h"

#include "NetClient.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyManager.h"


using namespace std;


class GameManager
{
	string input;
	Player* player;
	NetClient client;
	void server();


public:
	GameManager();
	~GameManager();
	void startGame();
	void runGame();
	void randomEncounters();
	void gameLoop();
	void magicGnome();
	//void gameLoop(Player& player);
protected:
	void Battle(Player *player, Enemy* enemy);
	void Shop();
	void Journey();

};

