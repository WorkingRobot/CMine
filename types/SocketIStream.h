#pragma once

#include <stdint.h>

class SocketIStream {
public:
	virtual int Read(char* data, uint32_t dataLength) = 0;
	virtual uint8_t ReadByte() = 0;

	virtual int32_t GetAvailableBufferSize() = 0;
};