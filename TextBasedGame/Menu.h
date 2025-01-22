#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "Player.h"
#include "GameManager.h"
using namespace std;

class Menu {
public:
	Menu();
	GameManager GM;
	void gameMenu();
	void startGame();
	void login();
	string username;
	string password;
	int menuChoice;
};

Menu::Menu() {
	menuChoice = 0;
}

void Menu::gameMenu() {
	
	string username;
	string password;

}

void Menu::login() {
	cout << "Username: ";
	cin >> username;
	cout << "\nPassword: ";
	cin >> password;

}

void Menu::startGame(){

	cout << "WELCOME TO THE GAME" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "1. Play" << endl;
	cout << "2. Exit" << endl;
	cin >> menuChoice;
	while (menuChoice != 1 || menuChoice != 2){
		cout << "\nPlease pick a valid choice." << endl;
		cin >> menuChoice;
	}
	switch (menuChoice) {
	//case'1': GM.StartGame();
	case'2': exit;
	} 
}