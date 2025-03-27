#ifndef SOCKET_BASE_H
#define SOCKET_BASE_H

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class Socket 
{
protected:
public:
    int sockfd;
    Socket();
    virtual ~Socket();

    void closeSocket();
    ssize_t sendData(int sock,const std::string& data);
    ssize_t recvData(int sock,std::string &buffer, size_t bufferSize);
};


#endif