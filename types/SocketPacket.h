#pragma once

#include "SocketPrimitives.h"

#include <memory>

struct SocketPacket {
	SocketVarInt Length;
	SocketVarInt PacketID;
	std::unique_ptr<char[]> PacketData;
};