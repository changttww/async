#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include "socket.h"

class ClientSocket : public Socket {
public:
    ClientSocket(const std::string &serverIP, int port);

    void send(const char * str);
    //~ClientSocket();
};

#endif // CLIENT_SOCKET_H
