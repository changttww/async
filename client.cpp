#include"client.h"

//创建socket、定义配置转换地址、连接服务器都在构造函数中
ClientSocket::ClientSocket(const std::string &serverIP, int port)
{
     //创建socket,封装后服务器和客户端句柄都是成员sockfd
     sockfd = socket(AF_INET,  SOCK_STREAM, 0);
     if(sockfd<0)
     {
         perror( "socket failed");
         exit(EXIT_FAILURE);
     }
 
     //定义并配置服务器地址
     struct sockaddr_in serverAddr;
     serverAddr.sin_family = AF_INET;
     serverAddr.sin_port = htons(port);
     
     //将 IP 地址从文本转换为二进制
     if(inet_pton(AF_INET,serverIP.c_str(), &serverAddr.sin_addr)<=0)
     {
         perror( "inet_pton failed");
         close(sockfd);
         exit(EXIT_FAILURE);
     }

    //连接服务器
    if(connect(sockfd,(struct sockaddr *)&serverAddr, sizeof(serverAddr))<0)
    {
        perror("Connection failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    // std::string buffer;
    // recvData(sockfd, buffer, 1024);
    // std::cout << "Server: " << buffer << std::endl;
 
}

void ClientSocket::send(const char* str)
{
    sendData(sockfd,str);
}

int main()
{
   
        ClientSocket client("127.0.0.1", 8080);
        std::string input;
        std::cout << "Client connected" << std::endl;
        while (true) 
        {
            std::cout << "Enter message (or 'quit' to exit): ";
            std::getline(std::cin, input);
            
            if (input == "quit") break;
            
            client.send(input.c_str());
            
            // 接收服务器的回显
            std::string response;
            if (client.recvData(client.sockfd, response, 1024) > 0) {
                std::cout << "Server echo: " << response << std::endl;
            }
        }
        
        return 0;  // 将 return 0 移到循环外面
}



//main函数实现
// #define PORT 8080
// #define SERVE_IP "127.0.0.1"


//     int sock = 0; //客户端socket
//     struct sockaddr_in serv_addr; //服务器的地址结构
//     char buffer[1024]={0};

    //基函数实现
    // //发送消息
    // const char* msg = "Hello from client";
    // send(sock,msg, strlen(msg),0);

    // //读取服务器消息
    // read(sock,buffer,sizeof(buffer));
    // std::cout << "Server:" << buffer << std::endl;

    // //关闭连接
    // close(sock);
