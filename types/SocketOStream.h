#pragma once

#include <stdint.h>

class SocketOStream {
public:
	virtual int Write(const char* data, uint32_t dataLength) = 0;
	virtual bool WriteByte(uint8_t value) = 0;
};