#include "SocketPacketIStream.h"

#include <vcruntime_string.h>

SocketPacketIStream::SocketPacketIStream(char* data, int32_t dataSize) {
	Data = data;
	Length = dataSize;
	Position = 0;
}

int SocketPacketIStream::Read(char* data, uint32_t dataLength) {
	if (dataLength == 0) return 0;
	int bytesRead = 0;
	while (dataLength > 0) {
		if (Position + dataLength > Length) {
			memcpy(data + bytesRead, Data + Position, Length - Position);
			bytesRead += Length - Position;
			dataLength -= Length - Position;
			return bytesRead;
		}
		else {
			memcpy(data + bytesRead, Data + Position, dataLength);
			Position += dataLength;
			bytesRead += dataLength;
			dataLength = 0;
		}
	}
	return bytesRead;
}

uint8_t SocketPacketIStream::ReadByte()
{
	if (Position < Length) {
		return Data[Position++];
	}
	else {
		return 0;
	}
}


int32_t SocketPacketIStream::GetAvailableBufferSize() {
	return Length - Position;
}