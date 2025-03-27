#include"server.h"

    //构造函数中创建socket，设置地址结构
    ServerSocket::ServerSocket(int port)
    {
        
        //创建socket并拿到句柄
        //AF_INET:IPV4
        //SOCK_STREAM:TCP、SOCK_DGRAM:UDP、SOCK_RAW:IP
        //0：默认协议、1：IPV4、2：IPV6
        //封装后句柄统一用sockfd
        sockfd = socket(AF_INET,SOCK_STREAM,0);
        if(sockfd == -1)
        {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }
        //设置服务器地址结构
        serverAddr.sin_family = AF_INET;//IPV4
        serverAddr.sin_addr.s_addr = INADDR_ANY;//监听所有可用端口
        serverAddr.sin_port = htons(port);//端口转换为网络字节序（小端->大端）

    }

    //绑定和监听合并到一起
    void ServerSocket::bindAndListen(int backlog)
    {
        //绑定结构体到句柄
     if(bind(sockfd, (struct sockaddr *)& serverAddr,sizeof(serverAddr))<0)
     {
         perror("Bind failed");
         close(sockfd);
         exit(EXIT_FAILURE);
     }  

     
    //监听端口
    //3：最大连接数,封装后换成backlog手动传入
    //port会在main函数中才被指定，函数中使用需要去地址结构体取
    if(listen(sockfd,backlog)<0)
    {
        perror("listen failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    std::cout << "Server listening on port" << ntohs(serverAddr.sin_port) << std::endl;
    }

    int ServerSocket::acceptConnection()
    {
        //接受客户端连接,此时创建局部的客户端地址结构体，拿到客户端句柄
        struct sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);
        int clientSock = accept(sockfd,(struct sockaddr*)&clientAddr,&clientLen);
        if(clientSock<0)
        {
            perror("accept failed");
            //close(server_fd);
            exit(EXIT_FAILURE);
        }
        std::cout<<"Client connected"<< inet_ntoa(clientAddr.sin_addr) << std::endl;
        return clientSock;
    }

    void ServerSocket::startEcho()
    {
        running = true;
        const size_t bufferSize = 1024;

        while(running)
        {
            int clientSock = acceptConnection();

            //也循环处理客户端的消息
            std::string buffer;
            while(running)
            {
                ssize_t bytesRead = recvData(clientSock,buffer,bufferSize);
                if(bytesRead<=0)
                {
                    std::cout << "Client disconnected" << std::endl;
                    break;
                }
                std::cout << "Client: " << buffer << std::endl;
                if(sendData(clientSock,buffer)<0)
                {
                    std::cout << "Failed to send data to client" << std::endl;
                    break;
                }
            }
            close(clientSock);
        }
    }


    int main()
    {
        ServerSocket server(8080);
        server.bindAndListen();
        std::cout << "Echo server started on port 8080" << std::endl;
        int clientSock = server.acceptConnection();
        server.startEcho();

        // std::string buffer;
        // server.recvData(clientSock, buffer, 1024);
        // std::cout << "Client: " << buffer << std::endl;

        // server.sendData(clientSock, "Hello from server");
        // close(clientSock);

        return 0;
    }

    