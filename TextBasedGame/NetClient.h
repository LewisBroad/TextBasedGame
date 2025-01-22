#ifndef NETCLIENT_H
#define NETCLIENT_H
#include <winsock2.h>
#include <WS2tcpip.h>
#include <tchar.h>
#include "iostream"

using namespace std;

class NetClient {
private:
    SOCKET clientSocket;
    int port;
    WSADATA wsaData;

public:
    NetClient(int port);
    ~NetClient();

    bool startUp();
    bool createSocket();
    bool connectToServer();
    void cleanup();
};

#endif // NETCLIENT_H