#include "SocketServer.h"

SocketServer::SocketServer()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
        perror("startup failed");
        exit(EXIT_FAILURE);
    }

    Socket = socket(AF_INET, SOCK_STREAM, 0);
    if (!Socket) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(25564);

    // Forcefully attaching socket to the port 8080 
    if (bind(Socket, (sockaddr*)&address, sizeof(address)))
    {
        printf("%d\n", WSAGetLastError());
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(Socket, SOMAXCONN) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (true) {
        SOCKET new_socket = accept(Socket, NULL, NULL);
        if (new_socket) {
            Connections.emplace_back(std::make_unique<SocketConnection>(new_socket, &EncData));
        }
        else {
            perror("accept");
            exit(EXIT_FAILURE);
            break;
        }
    }
}

SocketServer::~SocketServer()
{
    shutdown(Socket, SD_BOTH);
}
