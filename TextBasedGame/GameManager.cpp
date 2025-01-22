#include "GameManager.h"
GameManager::GameManager() {
	srand(time(NULL));
}
GameManager::~GameManager() {
	delete player;
}
void GameManager::startGame() {
	cout << "Welcome to the game\n";
	cout << "1. New Game\n2. Load Game\n";
	int choice;
	cin >> choice;

	if (choice == 1) {
		player = Player::PlayerCreation();
		cout << "\nStarting new game...\n";
	}
	else if (choice == 2) {
		//load game function
	}
	else {
		cerr << "Invalid option. Exiting...\n";
			exit(0);
	}
	gameLoop();
}
void GameManager::runGame() { //this is a code used for a simple battle scenario. Not used in actual game
	cout << "Game Started\n";
	Player* player = Player::PlayerCreation(); //runs player creation and assins to player pointer
	player->Display();
	Enemy* enemy = EnemyManager::createEnemy(player->getLevel()); //creats an enemy and assigns it to the enemy pointer.
	//gameLoop(player);
	Battle(player, enemy); //starts the battle script
}
void GameManager::gameLoop() {
	bool playing = true;
	while (playing && player->isAlive()) {
		cout << "\nYou are the wanderer\n\n";
		int randEncounter = rand() % 100; //number between 0-99
		if (randEncounter <30) { //30% chance of encounter
			system("CLS");
			randomEncounters(); //runs random encounters
		}
		else if (randEncounter < 40 && randEncounter >=30) {//10% chance of encounter
			system("CLS");
			magicGnome(); //runs the gnome encounter
		}
		cout << "\n\nDo you want to:\n";
		cout << "1. Continue walking\n";
		cout << "2. Check stats\n";
		cout << "3. Exit\n";
		int choice;
		cin >> choice;

		switch (choice) {
		case 1:
			system("CLS");
			continue; //will carry on the loop

		case 2:
			system("CLS");
			player->Display();
			continue;
		case 3:
			cout << "exiting...\n";
			playing = false;
			break; //will stop the loop
		}
	}
	if (!player->isAlive()) { //will end the game if the player is not alive
		cout << "You have died. Game Over\n";
		playing = false;
	}
}
//void GameManager::gameLoop(Player &player) {
//	while (player.isAlive()) {
//		auto enemy = EnemyManager::createEnemy(player.getLevel());
//		cout << "\nA level "<<enemy->getLevel()<< " " << enemy->getName() << " blocks your path\n";
//		enemy->Display();
//		while (enemy->isAlive() && player.isAlive()) {
//			//players turn
//			int choice; 
//			cout << "\nChoose your attack:\n 1. Physical Damage\n 2.Magic Damage\n";
//			cin >> choice;
//			if (choice == 1) {
//				enemy->takePhysicalDamage(player.physicalAttack());
//			}
//			else if (choice == 2) {
//				enemy->takeMagicDamage(player.magicAttack());
//			}
//			else {
//				cout << "Undecided, skipping turn...\n";
//			}
//			if (enemy->isAlive()) {
//				if (rand() % 2 == 0) {
//					player.takePhysicalDamage(enemy->physicalAttack());
//				}
//				else {
//					player.takeMagicDamage(enemy->magicAttack());
//				}
//			}
//		}
//		if (player.isAlive()) {
//			cout << "You Defeated the " << enemy->getName() << endl;
//			player.gainXP(20 * enemy->getLevel());
//		}
//		else { cout << "you have died\n"; }
//	}
//}

void GameManager::randomEncounters() {
	cout << "\nA Wild Enemy Appers";
	Enemy* enemy = EnemyManager::createEnemy(player->getLevel()); //calls the enemy manager to automatically create an enemy
	enemy->Display(); //display enemy stats
	cout << "\n\nYOUR STATS:\n";
	player->Display(); //display player stats

	cout << "\nDo you want to:\n";
	cout << "1. Fight\n";
	cout << "2. Flee\n";
	int choice;
	cin >> choice;
	if (choice == 1) {
		cout << "\nYou stand ready to fight!\n";
		Battle(player, enemy); //starts battle loop
	}
	else if (choice == 2) {
		cout << "You attempt to flee...\n";
		if (rand() % 100 < 50) {//50% chance to flee
			cout << "You have fled\n\n";
		}
		else {
			cout << "You failed to flee. \n";
			Battle(player, enemy);
		}
	}
	else {
		cerr << "invalid option. Combat starts\n";
		Battle(player, enemy);
	}
	delete enemy; // free up memory
}

void GameManager::Battle(Player* player, Enemy* enemy) {
	while (player->isAlive() && enemy->isAlive()) { //will keep running while both enemy and player are alive
		//players turn
		int choice;
		cout << "\nChoose your attack:\n 1. Physical Damage\n 2.Magic Damage\n";
		cin >> choice;
		if (choice == 1) {
			enemy->takePhysicalDamage(player->physicalAttack()); //runs damage on enemy based on players attack damage
			cout << "Enemy HP: " << enemy->getHealth() << endl;
		}
		else if (choice == 2) {
			enemy->takeMagicDamage(player->magicAttack()); //runs damage on enemy based on players attack damage
			cout << "Enemy HP: "<< enemy->getHealth() << endl;
		}
		else {
			cout << "Undecided, skipping turn...\n";
		}
		//Enemy's turn
		if (enemy->isAlive()) {
			int difference = 3;
			/*if (rand() % 2 == 0) { //random number outcome always 0 or 1. randomly selects damage type.
				player->takePhysicalDamage(enemy->physicalAttack());
				cout << player->getName() << " HP: " << player->getHealth() << endl;
			}
			else {
				player->takeMagicDamage(enemy->magicAttack());
				cout << player->getName() << " HP: " << player->getHealth() << endl;

			}*/
 
			//smart enemy damage. Will attack based on what will do more damage.
			if (abs(enemy->physicalAttack() - enemy->magicAttack()) > difference) { //abs is used to get the absolute difference between the numbers
				if (enemy->physicalAttack() > enemy->magicAttack()) {
					player->takePhysicalDamage(enemy->physicalAttack());
					cout << player->getName() << " HP: " << player->getHealth() << endl;
				}
				else {
					player->takeMagicDamage(enemy->magicAttack());
					cout << player->getName() << " HP: " << player->getHealth() << endl;
				}
			}
			else { //if the enemy damage isn't much of a difference, the enemy will look at the players resistance instead.
				if (player->getPhysicalResist() > player->getMagicResist()) {
					player->takeMagicDamage(enemy->magicAttack());
					cout << player->getName() << " HP: " << player->getHealth() << endl;
				}
				else {
					player->takePhysicalDamage(enemy->physicalAttack());
					cout << player->getName() << " HP: " << player->getHealth() << endl;
				}

			}

		}
	}
	if (player->isAlive()) {
		system("CLS");
		cout << "You Defeated the " << enemy->getName() << endl;
		player->gainXP(20 * enemy->getLevel());
	}
	else { cout << "you have died\n"; delete player; }
}

void GameManager::magicGnome() {
	Enemy* enemy = new Gnome("Evil Magic Gnome", player->getLevel()); //manually creates an enemy
	cout << "\nYou encounter a magical gnome\n";
	cout << "The gnome offers you a magical upgrade\n";
	int buff = rand() % 3; //3 random buffs
	switch (buff) {
	case 0: {
		int healing = player->getLevel() * 10;
		cout << "The gnome heals you for " << healing << " health!\n";
		player->heal(healing);
		break;
	}
	case 1: {
		int boostAttack = rand() % 11;
		if (boostAttack <= 0) {
			cout << "The gnome laughs at you instead of healing\n";
		}
		else {
			cout << "The gnome boosts your main attack by " << boostAttack << endl;
			player->boostAttack(boostAttack);
		}
		break;
		}
	case 3: {
		int resistBoost = 4 + rand() % 5;
		cout << "The gnome boosts your armour and magic resist by " << resistBoost << endl;
		player->resistBoost(resistBoost);
		break;
	}
	default:
		cout << "The gnome laughs at you and instead leaves\n";
		break;
	}
	cout << "\nDo you: \n";
	cout << "1.Thank him\n";
	cout << "2. Leave\n";
	int choice;
	cin >> choice;
	switch (choice) {
	case 1: {
		cout << "\nHe nods and vanishes\n";
		break;
	}
	case 2: {
		cout << "\nYou hear a wimper behind you as you leave\n";
		break;
	}
	default: {
		cout << "\nYou start to notice something about the gnome...\n";
		Sleep(1000);
		cout << "\nSomething sinister...";
		Sleep(1000);
		cout << "\nYou see the evil in its eyes\n";
		Sleep(5000);
		cout << "\n The Gnome transforms into " << enemy->getName();
		Battle(player, enemy);
	}
	}
	delete enemy;
}

void GameManager::Shop() {

}
void GameManager::Journey() {

}
