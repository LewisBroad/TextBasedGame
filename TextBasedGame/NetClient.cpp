#include "NetClient.h"
#include <stdexcept>

NetClient::NetClient() : clientSocket(INVALID_SOCKET){
	WSADATA wsaData;
if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
	throw runtime_error("WSAStartup failed");
	} 
}
NetClient::~NetClient() {
	closeConnection();
	WSACleanup();
}
bool NetClient::initialize() {
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) {
		cerr << "Error creating socket: " << WSAGetLastError() << endl;
		return false;
	}
	return true;
}
bool NetClient::connectToServer(const string& ipAddress, int port) {
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &serverAddr.sin_addr);
	if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		cerr << "Failed to connect to server: " << WSAGetLastError() << endl;
		return false;
	}
	cout << "Connected to server\n";
	return true;
