//Lewis Andrew Broad. Buckinghamshire New University

#include "NetClient.h"

NetClient::NetClient() :clientSocket(INVALID_SOCKET), isConnected(false)
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cerr << "Failed to initialise Winsock: " << WSAGetLastError() << endl;
		throw runtime_error("Winsock initialisation failed");
	}
}

NetClient::~NetClient() {
	closeConnection();
	WSACleanup();
}

bool NetClient::connectToServer(const string& ipAddress, int port) {
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        cerr << "Socket creation failed: " << WSAGetLastError() << endl;
        return false;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    if (InetPton(AF_INET, ipAddress.c_str(), &serverAddr.sin_addr) <= 0) {
        cerr << "Invalid IP address format." << endl;
        closesocket(clientSocket);
        return false;
    }

    if (connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "Failed to connect to the server: " << WSAGetLastError() << endl;
        closesocket(clientSocket);
        return false;
    }

    isConnected = true;
    cout << "Connected to the server!" << endl;
    return true;
}
bool NetClient::sendMessage(const string& message) {
	if (!isConnected) {
		cerr << "Not connected to the server." << endl;
		return false;
	}
	if (send(clientSocket, message.c_str(), message.length(), 0) == SOCKET_ERROR) {
		cerr << "Failed to send message: " << WSAGetLastError() << std::endl;
		return false;
	}
	return true;
}

string NetClient::reciveMessage() {
	if (!isConnected) {
		cerr << "Not connected to the server." << endl;
		return "";
	}
	char buffer[512];
	int bytesReceived = recv(clientSocket, buffer,sizeof(buffer), 0);
	if (bytesReceived > 0) {
		return string(buffer, bytesReceived);
	}
	else if (bytesReceived == 0) {
		cerr << "Connection closed by the server." << endl;
	}
	else {
		cerr << "Failed to receive message: " << WSAGetLastError() << endl;
	}
	return "";
}

void NetClient::closeConnection() {
	if (isConnected) {
		closesocket(clientSocket);
		clientSocket = INVALID_SOCKET;
		isConnected = false;
		cout << "Connection closed." << endl;
	}
}