#pragma once

#include "../types/SocketPrimitives.h"

struct CBSetExperience {
    const int Id = 0x48;

    SocketFloat XPBar;
    SocketVarInt Level;
    SocketVarInt TotalXP;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBSetExperience& out) {
        return sock
            << out.XPBar
            << out.Level
            << out.TotalXP;
    }
};