#include "NetClient.h"

NetClient::NetClient(int port) : clientSocket(INVALID_SOCKET), port(port) {}

NetClient::~NetClient() {
    cleanup();
}

bool NetClient::startUp() {
    WORD wVersionRequested = MAKEWORD(2, 2);
    int wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if (wsaerr != 0) {
        cout << "The Winsock DLL not found!" << endl;
        return false;
    }
    cout << "The Winsock DLL found!" << endl;
    cout << "The status: " << wsaData.szSystemStatus << endl;
    return true;
}

bool NetClient::createSocket() {
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        return false;
    }
    cout << "Socket() is OK!" << endl;
    return true;
}

bool NetClient::connectToServer() {
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_port = htons(port);

    InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);

    if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
        cout << "Client: connect() - Failed to connect." << endl;
        WSACleanup();
        return false;
    }

    cout << "Client: connect() is OK." << endl;
    cout << "Client: Can start sending and receiving data..." << endl;
    return true;
}

void NetClient::cleanup() {
    if (clientSocket != INVALID_SOCKET) {
        closesocket(clientSocket);
        clientSocket = INVALID_SOCKET;
    }
    WSACleanup();
    cout << "Client: Cleaned up and closed." << endl;
}
