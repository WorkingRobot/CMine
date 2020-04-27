#pragma once

#include "../types/SocketPrimitives.h"

struct SBUpdateCmd {
    static const int Id = 0x24;

    SocketPosition Location;
    SocketString Command;
    SocketVarInt Mode; // 0: chain, 1: repeat, 2: impulse
    SocketByte Flags; // 0x1: track output, 0x2: conditional, 0x4: doesn't need redstone

    friend SocketIStream& operator>>(SocketIStream& sock, SBUpdateCmd& out) {
        return sock
            >> out.Location
            >> out.Command
            >> out.Mode
            >> out.Flags;
    }
};