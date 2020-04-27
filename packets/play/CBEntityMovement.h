#pragma once

#include "../types/SocketPrimitives.h"

struct CBEntityMovement {
    static const int Id = 0x2C;

    SocketVarInt EntityId;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBEntityMovement& out) {
        return sock
            << out.EntityId;
    }
};