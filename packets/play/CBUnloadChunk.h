#pragma once

#include "../types/SocketPrimitives.h"

struct CBUnloadChunk {
    const int Id = 0x1E;

    SocketInt ChunkX;
    SocketInt ChunkZ;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBUnloadChunk& out) {
        return sock
            << out.ChunkX << out.ChunkZ;
    }
};