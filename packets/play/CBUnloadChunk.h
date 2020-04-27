#pragma once

#include "../types/SocketPrimitives.h"

struct CBUnloadChunk {
    static const int Id = 0x1E;

    SocketInt ChunkX;
    SocketInt ChunkZ;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBUnloadChunk& out) {
        return sock
            << out.ChunkX << out.ChunkZ;
    }
};