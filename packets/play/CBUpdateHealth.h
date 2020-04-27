#pragma once

#include "../types/SocketPrimitives.h"

struct CBUpdateHealth {
    const int Id = 0x49;

    SocketFloat Health;
    SocketVarInt Food;
    SocketFloat Saturation;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBUpdateHealth& out) {
        return sock
            << out.Health
            << out.Food
            << out.Saturation;
    }
};