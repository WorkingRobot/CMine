#pragma once

#include "../types/SocketPrimitives.h"

struct SBPlayerDigging {
    static const int Id = 0x1A;

    SocketVarInt Status; // 0-6
    SocketPosition Location;
    SocketByte Face; // 0-5

    friend SocketIStream& operator>>(SocketIStream& sock, SBPlayerDigging& out) {
        return sock
            >> out.Status
            >> out.Location
            >> out.Face;
    }
};