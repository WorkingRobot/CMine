#include "SocketPacketOStream.h"

#include <vcruntime_string.h>

SocketPacketOStream::SocketPacketOStream(SocketVarInt&& packetId) {
	Data.reserve(32);
	PacketID = packetId;
}

int SocketPacketOStream::Write(const char* data, uint32_t dataLength) {
	if (dataLength == 0) return 0;
	Data.insert(Data.end(), data, data + dataLength);
	return dataLength;
}

bool SocketPacketOStream::WriteByte(uint8_t value) {
	Data.emplace_back(value);
	return true;
}