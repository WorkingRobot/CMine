#pragma once

#include "../types/SocketPrimitives.h"

struct CBEntityAttach {
    static const int Id = 0x45;

    SocketInt AttatchedId;
    SocketInt HoldingId;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBEntityAttach& out) {
        return sock
            << out.AttatchedId
            << out.HoldingId;
    }
};