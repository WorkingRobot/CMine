#pragma once

#include "../types/SocketPrimitives.h"

struct CBUpdateViewPos {
    static const int Id = 0x41;

    SocketVarInt ChunkX;
    SocketVarInt ChunkZ;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBUpdateViewPos& out) {
        return sock
            << out.ChunkX << out.ChunkZ;
    }
};