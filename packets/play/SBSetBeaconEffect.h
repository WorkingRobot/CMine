#pragma once

#include "../types/SocketPrimitives.h"

struct SBSetBeaconEffect {
    static const int Id = 0x22;

    SocketVarInt PrimaryId;
    SocketVarInt SecondaryId;

    friend SocketIStream& operator>>(SocketIStream& sock, SBSetBeaconEffect& out) {
        return sock
            >> out.PrimaryId
            >> out.SecondaryId;
    }
};