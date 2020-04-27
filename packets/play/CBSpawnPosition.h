#pragma once

#include "../types/SocketPrimitives.h"

struct CBSpawnPosition {
    const int Id = 0x4E;

    SocketPosition Location;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBSpawnPosition& out) {
        return sock
            << out.Location;
    }
};