#pragma once

#include "../types/SocketPrimitives.h"

struct CBBlockChange {
    static const int Id = 0x0C;

    SocketPosition Location;
    SocketVarInt BlockId;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBBlockChange& out) {
        return sock
            << out.Location
            << out.BlockId;
    }
};