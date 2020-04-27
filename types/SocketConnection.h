#pragma once
#include "SocketIStream.h"
#include "SocketOStream.h"
#include "SocketPacket.h"
#include "../encryption/ServerEnc.h"
#include "../cancel_flag.h"

#include <winsock2.h>

#include <thread>

enum class ConnectionState {
	Handshaking,
	Status,
	Login,
	Play
};

class SocketConnection : SocketIStream, SocketOStream {
public:
	SocketConnection(SOCKET socket, ServerEnc* encSrv);
	~SocketConnection();

	int Write(const char* data, uint32_t dataLength);
	bool WriteByte(uint8_t value);
	int Read(char* data, uint32_t dataLength);
	uint8_t ReadByte();
	int32_t GetAvailableBufferSize();

	uint8_t PeekByte();

private:
	bool RefillBuffer();
	void HandlePacket(SocketPacket& packet);

	void ConnectionThread();

	ConnectionState State;
	bool CompressionEnabled;
	bool EncryptionEnabled;
	ENC_CTX EncCtx;
	ServerEnc* EncSrv;

	SOCKET Socket;
	std::thread Thread;
	cancel_flag Flag;
	int RecvInd;
	int RecvSize;
	char* RecvBuffer;
};