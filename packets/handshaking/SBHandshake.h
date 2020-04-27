#pragma once

#include "../types/SocketPrimitives.h"

struct SBHandshake {
    SocketVarInt ProtocolVersion;
    SocketString ServerAddress;
    SocketUShort ServerPort;
    SocketVarInt NextState;

    friend SocketIStream& operator>>(SocketIStream& sock, SBHandshake& out) {
        sock >> out.ProtocolVersion;
        sock >> out.ServerAddress;
        sock >> out.ServerPort;
        sock >> out.NextState;
        return sock;
    }
};