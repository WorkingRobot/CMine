#pragma once

#include "../types/SocketPrimitives.h"

struct CBSpawnXPOrb {
    const int Id = 0x01;

    SocketVarInt EntityId;
    SocketDouble X;
    SocketDouble Y;
    SocketDouble Z;
    SocketShort Count;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBSpawnXPOrb& out) {
        return sock
            << out.EntityId
            << out.X << out.Y << out.Z
            << out.Count;
    }
};