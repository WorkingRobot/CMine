#pragma once

#include "SocketOStream.h"
#include "SocketPrimitives.h"

#include <vector>

class SocketPacketOStream : public SocketOStream {
public:
	SocketPacketOStream(SocketVarInt&& packetId);

	int Write(const char* data, uint32_t dataLength);
	bool WriteByte(uint8_t value);

    friend SocketOStream& operator<<(SocketOStream& sock, const SocketPacketOStream& out) {
		SocketVarInt Length;
		Length.Value = out.Data.size() + out.PacketID.GetSize();
		printf("Writing packet id %02x, size %d\n", out.PacketID.Value, Length);
		sock << Length << out.PacketID;
		sock.Write(out.Data.data(), out.Data.size());
        return sock;
    }

private:
	std::vector<char> Data;
	SocketVarInt PacketID;
};