#pragma once

#include "../types/SocketPrimitives.h"

struct CBRemoveEntityEffect {
    const int Id = 0x39;

    SocketVarInt EntityId;
    SocketByte EffectId;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBRemoveEntityEffect& out) {
        return sock
            << out.EntityId
            << out.EffectId;
    }
};