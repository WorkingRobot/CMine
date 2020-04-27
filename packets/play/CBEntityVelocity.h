#pragma once

#include "../types/SocketPrimitives.h"

struct CBEntityVelocity {
    static const int Id = 0x46;

    SocketVarInt EntityId;
    SocketShort VelX;
    SocketShort VelY;
    SocketShort VelZ;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBEntityVelocity& out) {
        return sock
            << out.EntityId
            << out.VelX << out.VelY << out.VelZ;
    }
};