#include <iostream>
#include <cstring>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 8080
#define SERVE_IP "127.0.0.1"

int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024]={0};

    sock = socket(AF_INET,  SOCK_STREAM, 0);
    if(sock<0)
    {
        perror( "socket failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    if(inet_pton(AF_INET, SERVE_IP, &serv_addr.sin_addr)<=0)
    {
        perror( "inet_pton failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    if(connect(sock,(struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    const char* msg = "Hello from client";
    send(sock,msg, strlen(msg),0);

    read(sock,buffer,sizeof(buffer));
    std::cout << "Server:" << buffer << std::endl;

    close(sock);

    return 0;


}