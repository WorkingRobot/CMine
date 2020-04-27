#pragma once

#include <winsock2.h>

#include <memory>
#include <vector>

#include "SocketConnection.h"
#include "../encryption/ServerEnc.h"

class SocketServer {
public:
	SocketServer();
	~SocketServer();

	ServerEnc EncData;

private:
	SOCKET Socket;
	std::vector<std::unique_ptr<SocketConnection>> Connections;

};