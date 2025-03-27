#include "socket.h"

//Socket::Socket():sockfd(-1){}

Socket::Socket()
{
    if(sockfd != -1) close(sockfd);
}

void Socket::closeSocket()
{
    if(sockfd != -1)
    {
        close(sockfd);
        sockfd = -1;
    }
}

ssize_t Socket::sendData(int sock,const std::string& data)
{
    //循环发送消息，直到发送完毕
    size_t totalSent = 0;
    size_t dataSize = data.size();
    while(totalSent<dataSize)
    {
        ssize_t sent = send(sock,data.c_str()+totalSent,dataSize-totalSent,0);
        if(sent<0)
        {
            perror("send failed");
            return -1;
        }
        totalSent += sent;
    }

    return totalSent;
}

ssize_t Socket::recvData(int sock,std::string &buffer, size_t bufferSize)
{
    char temp [bufferSize] = {0};
    ssize_t byteRead = recv(sock,temp,bufferSize-1,0);
    if(byteRead>0)
    {
        buffer.assign(temp,byteRead);
    }
    return byteRead;
}

Socket::~Socket()
{
    closeSocket();
}