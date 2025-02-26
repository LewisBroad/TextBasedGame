//Lewis Andrew Broad. Buckinghamshire New University
#include <iostream>
#include <iomanip>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

using namespace std;

#include "GameManager.h"
#include "Character.h"
#include "Player.h"
#include "NetClient.h"


int main() {
	//const int port = 55555;
	//NetClient client(port);
	//if there are any errors in the client startup, return 1
	//if (!client.startUp()) return 1; 
	//if (!client.createSocket()) return 1;
	//if (!client.connectToServer()) return 1;



	GameManager gm;
	gm.startGame();



	//client.cleanup();
	return 0;
}
