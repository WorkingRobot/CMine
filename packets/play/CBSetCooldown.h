#pragma once

#include "../types/SocketPrimitives.h"

struct CBSetCooldown {
    static const int Id = 0x18;

    SocketVarInt ItemId;
    SocketVarInt Cooldown; // in ticks

    friend SocketOStream& operator<<(SocketOStream& sock, const CBSetCooldown& out) {
        return sock
            << out.ItemId
            << out.Cooldown;
    }
};