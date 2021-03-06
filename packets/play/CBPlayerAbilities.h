#pragma once

#include "../types/SocketPrimitives.h"

struct CBPlayerAbilities {
    static const int Id = 0x32;

    SocketByte Flags; // 0x01: invulnerable, 0x02: flying, 0x04: allow flying, 0x08: creative mode
    SocketFloat FlySpeed; // 0.05 default
    SocketFloat FovModifier; // 0.1 default

    friend SocketOStream& operator<<(SocketOStream& sock, const CBPlayerAbilities& out) {
        return sock
            << out.Flags
            << out.FlySpeed
            << out.FovModifier;
    }
};