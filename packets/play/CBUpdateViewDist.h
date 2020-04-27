#pragma once

#include "../types/SocketPrimitives.h"

struct CBUpdateViewDist {
    static const int Id = 0x42;

    SocketVarInt Distance; // 2-32

    friend SocketOStream& operator<<(SocketOStream& sock, const CBUpdateViewDist& out) {
        return sock
            << out.Distance;
    }
};