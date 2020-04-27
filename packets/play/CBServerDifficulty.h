#pragma once

#include "../types/SocketPrimitives.h"

struct CBServerDifficulty {
    const int Id = 0x0E;

    SocketByte Difficulty; // 0 peaceful -> 3 hard
    SocketBool Locked;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBServerDifficulty& out) {
        return sock
            << out.Difficulty
            << out.Locked;
    }
};