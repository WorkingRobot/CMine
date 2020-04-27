#pragma once

#include "../types/SocketPrimitives.h"

struct CBEntityAnim {
    static const int Id = 0x06;

    SocketVarInt EntityId;
    SocketByte Animation;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBEntityAnim& out) {
        return sock
            << out.EntityId
            << out.Animation;
    }
};