#pragma once

#include "../types/SocketPrimitives.h"

struct CBCamera {
    static const int Id = 0x3F;

    SocketVarInt EntityId;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBCamera& out) {
        return sock
            << out.EntityId;
    }
};