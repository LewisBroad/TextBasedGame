// MiniGame.cpp : Defines the entry point for the application.
#include <iostream>
#include <iomanip>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

using namespace std;

#include "Menu.h"
#include "Character.h"
#include "Player.h"

void main() {

	GameManager gm;
	gm.startGame();

}
