//Lewis Andrew Broad. Buckinghamshire New University

#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>
using namespace std;

class NetClient
{
private:
	SOCKET clientSocket;
	sockaddr_in serverAddr;
	bool isConnected;
public:
	NetClient();
	~NetClient();

	bool connectToServer(const string& ipAddress, int port);
	bool sendMessage(const string& message);
	string reciveMessage();
	void closeConnection();


};

