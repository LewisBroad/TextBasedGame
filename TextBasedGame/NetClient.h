#include <winsock2.h>
#include <iostream>
using namespace std;

class NetClient
{
private:
	SOCKET clientSocket;
	sockaddr_in serverAddr;

public:
	NetClient();
	~NetClient();
	bool initialize();
	bool connectToServer(const string& ipAddress, int port);
	bool sendToServer(string message);
	string receiveFromServer();
	void closeConnection();
};

