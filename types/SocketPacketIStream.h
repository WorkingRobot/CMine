#pragma once

#include "SocketIStream.h"

class SocketPacketIStream : public SocketIStream {
public:
	SocketPacketIStream(char* data, int32_t dataSize);

	int Read(char* data, uint32_t dataLength);
	uint8_t ReadByte();
	int32_t GetAvailableBufferSize();

private:
	char* Data;
	int32_t Length;
	int32_t Position;
};