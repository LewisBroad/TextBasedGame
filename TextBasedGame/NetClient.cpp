#include "NetClient.h"

NetClient::NetClient(int port) : clientSocket(INVALID_SOCKET), port(port) {} //initialises the clientSocket and port

NetClient::~NetClient() { //destructor ensures cleanup
    cleanup();
}

bool NetClient::startUp() { //initialises the Winsock dll and checks for errors
    WORD wVersionRequested = MAKEWORD(2, 2);
	int wsaerr = WSAStartup(wVersionRequested, &wsaData); //initialises the Winsock dll
	if (wsaerr != 0) { //check for errors
        cout << "The Winsock DLL not found!" << endl;
        return false;
    }
    cout << "The Winsock DLL found!" << endl;
	cout << "The status: " << wsaData.szSystemStatus << endl; //displays the status of the Winsock dll
    return true;
}

bool NetClient::createSocket() { //creates a socket and check for errors
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //creates a socket
	if (clientSocket == INVALID_SOCKET) { //check for errors
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        return false;
    }
	cout << "Socket() is OK!" << endl; //socket created successfully
    return true;
}

bool NetClient::connectToServer() { //connects to the server and check for errors
	sockaddr_in clientService; //creates a sockaddr_in object
    clientService.sin_family = AF_INET; 
	clientService.sin_port = htons(port); //sets the port

	InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr); //sets the IP address

	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) { //connects to the server
        cout << "Client: connect() - Failed to connect." << endl; 
		WSACleanup();//cleans up the Winsock dll
        return false;
    }

    cout << "Client: connect() is OK." << endl;
    cout << "Client: Can start sending and receiving data..." << endl;
    return true;
}

void NetClient::cleanup() { //closes the socket and cleans up the Winsock dll
    if (clientSocket != INVALID_SOCKET) {
        closesocket(clientSocket);
        clientSocket = INVALID_SOCKET;
    }
    WSACleanup();
    cout << "Client: Cleaned up and closed." << endl;
}
