//Lewis Andrew Broad. Buckinghamshire New University

#include "GameManager.h"


GameManager::GameManager() {
	srand(time(NULL)); //seed the random number generator
}
GameManager::~GameManager() {
	delete player; //frees up memory from player object
}
void GameManager::startGame() {
	try {
		cout << "Welcome to the game\n";
		cout << "1. New Game\n2. Load Game\n";
		int choice;
		cin >> choice;

		if (cin.fail()) throw invalidActionExeption(); //if the input is not an integer, throw an exception

		if (choice == 1) {
			player = Player::PlayerCreation(); //creates a new player object
			cout << "\nStarting new game...\n";
		}
		else if (choice == 2) {
			//load game function
		}
		else {
			cerr << "Invalid option. Exiting...\n";
			exit(0); //closes the program
		}
		gameLoop();
	}
	catch (ExceptionHandler& e) {
		cerr << "Error: " << e.what() << endl; //exception handler
		exit(1);
	}
}

void GameManager::gameLoop() {

		bool playing = true; //keeps the game running
		while (playing && player->isAlive()) { //game loop will run while the player is alive
			cout << "\nYou are the wanderer\n\n";
			int randEncounter = rand() % 100; //number between 0-99
			if (randEncounter < 30) { //30% chance of encounter
				system("CLS");
				randomEncounters(); //runs random encounters
			}
			else if (randEncounter < 40 && randEncounter >= 30) {//10% chance of encounter
				system("CLS");
				magicGnome(); //runs the gnome encounter
			}
			else {
				cout << "You continue to walk...\n";
			}
			cout << "\n\nDo you want to:\n";
			cout << "1. Continue walking\n";
			cout << "2. Check stats\n";
			cout << "3. Exit\n";
			int choice;
			
			cin >> choice;
			try{
			switch (choice) {
			case 1:
				system("CLS"); //clears the screen
				continue; //will carry on the loop

			case 2:
				system("CLS");
				player->Display(); //calls player display function
				continue;
			case 3:
				cout << "exiting...\n";
				playing = false;
				break; //will stop the loop
			default:
				throw invalidActionExeption(); //handles invalid choice
				
			}
		}
			catch (ExceptionHandler& e) {
				cerr << "Error: " << e.what() << endl; //print error if caught will only catch if the choice is invalid
			}
		}
		if (!player->isAlive()) { //will end the game if the player is not alive
			cout << "You have died. Game Over\n";
			playing = false;
		}
}

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
	try {
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
	}
	catch (ExceptionHandler& e) {
		cerr << "Error: " << e.what() << endl;
	}

	delete enemy; // free up memory
}



void GameManager::Battle(Player* player, Enemy* enemy) {

	AttackFunction attacks[] = {&GameManager::physicalAttack,&GameManager::magicAttack }; //array of function pointers

	while (player->isAlive() && enemy->isAlive()) { //will keep running while both enemy and player are alive
		//players turn
		int choice;
		cout << "\nChoose your attack:\n 1. Physical Damage\n 2.Magic Damage\n";
		cin >> choice;
		if (choice >= 1 && choice <= 2) {
			(this->*attacks[choice - 1])(player, enemy); //calls the attack function based on the choice. 1 being physical damage and 2 being magic damage
		}
		else {
			cout << "Undecided, skipping turn...\n";
		}
		//Enemy's turn
		if (enemy->isAlive()) {
			int difference = 3; 
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
		player->Display(true);
	}
	else { cout << "you have died\n"; delete player; } //free up memory
}

void GameManager::magicGnome() {
	Enemy* enemy = new Gnome("Evil Magic Gnome", player->getLevel()); //manually creates an enemy
	cout << "\nYou encounter a magical gnome\n";
	cout << "The gnome offers you a magical upgrade\n";
	int buff = rand() % 3; //3 random buffs chosen from
	switch (buff) {
	case 0: {
		int healing = player->getLevel() * 10;
		cout << "The gnome heals you for " << healing << " health!\n";
		player->heal(healing); //heals the player for amount
		break;
	}
	case 1: {
		int boostAttack = rand() % 11;
		if (boostAttack <= 0) {
			cout << "The gnome laughs at you instead of healing\n"; //gnome does nothing.
		}
		else {
			cout << "The gnome boosts your main attack by " << boostAttack << endl;
			player->boostAttack(boostAttack); //boosts the players attack
		}
		break;
		}
	case 3: {
		int resistBoost = 4 + rand() % 5;
		cout << "The gnome boosts your armour and magic resist by " << resistBoost << endl;
		player->resistBoost(resistBoost); //boosts the players resistances
		break;
	}
	default:
		cout << "The gnome laughs at you and instead leaves\n"; //default behaviour. does nothing.
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
		Battle(player, enemy); //battle the gnonme that was created earlier.
	}
	}
	delete enemy;
}

void GameManager::physicalAttack(Player* player, Enemy* enemy) {
	enemy->takePhysicalDamage(player->physicalAttack()); //calls the take physical damage function and bases the damage on the players physical attack
	cout << "You deal " << player->physicalAttack() << " physical damage.\n";
	cout << "Enemy health: " << enemy->getHealth() << endl;
}
void GameManager::magicAttack(Player* player, Enemy* enemy) {
	enemy->takePhysicalDamage(player->magicAttack());
	cout << "You deal " << player->magicAttack() << " magic damage.\n";
	cout << "Enemy health: " << enemy->getHealth() << endl;

}



void GameManager::Shop() {

}
void GameManager::Journey() {

}



