#include <iostream>
#include <cstring>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

#define PORT 8080

int main()
{
    //声明句柄、地址结构体
    int server_fd,new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[1024]={0};

    //创建socket并拿到句柄
    server_fd = socket(AF_INET,SOCK_STREAM,0);
    if(server_fd == -1)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //绑定ip和端口到结构体
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    //绑定结构体到句柄
    if(bind(server_fd, (struct sockaddr *)&address,sizeof(address))<0)
    {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }    

    //监听端口
    if(listen(server_fd,3)<0)
    {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    std::cout << "Server listening on port" << PORT << std::endl;

    //接受客户端连接
    new_socket = accept(server_fd,(struct sockaddr*)&address,&addrlen);
    if(new_socket<0)
    {
        perror("accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    //读取客户端消息
    read(new_socket,buffer,sizeof(buffer));
    std::cout<<"Client:" << buffer << std::endl;

    //发送响应
    const char*msg = "Hello from server";
    send(new_socket,msg,strlen(msg),0);

    close(new_socket);
    close(server_fd);

    return 0;
}