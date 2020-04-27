#pragma once

#include "../types/SocketPrimitives.h"

struct CBDisplayScoreboard {
    const int Id = 0x43;

    SocketByte Position; // 0: list, 1: sidebar, 2: belowname, 3-18: team sidebar
    SocketString ScoreName;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBDisplayScoreboard& out) {
        return sock
            << out.Position
            << out.ScoreName;
    }
};