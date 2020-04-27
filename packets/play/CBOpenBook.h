#pragma once

#include "../types/SocketPrimitives.h"

struct CBOpenBook {
    const int Id = 0x2E;

    SocketVarInt Hand; // 0: main hand, 1: off hand

    friend SocketOStream& operator<<(SocketOStream& sock, const CBOpenBook& out) {
        return sock
            << out.Hand;
    }
};