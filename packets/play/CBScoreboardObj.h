#pragma once

#include "../types/SocketPrimitives.h"

struct CBScoreboardObj {
    const int Id = 0x4A;

    SocketString Name;
    SocketByte Mode; // 0: create, 1: remove, 2: update text
    std::optional<SocketChat> Value;
    std::optional<SocketVarInt> Type; // 0: integer, 1: hearts

    friend SocketOStream& operator<<(SocketOStream& sock, const CBScoreboardObj& out) {
        sock
            << out.Name
            << out.Mode;
        if (out.Mode == 0 || out.Mode == 2) {
            sock
                << out.Value.value()
                << out.Type.value();
        }
        return sock;
    }
};