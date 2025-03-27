#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include "socket.h"

class ServerSocket : public Socket {
private:
    struct sockaddr_in serverAddr;
    bool running;

public:
    explicit ServerSocket(int port);
    //~ServerSocket();

    void bindAndListen(int backlog = 3);
    int acceptConnection();
    void startEcho();  
};

#endif // SERVER_SOCKET_H
