#pragma once

#include "../types/SocketPrimitives.h"

struct CBEntityStatus {
    const int Id = 0x1C;

    SocketInt EntityId;
    SocketByte EntityStatus; // enum

    friend SocketOStream& operator<<(SocketOStream& sock, const CBEntityStatus& out) {
        return sock
            << out.EntityId
            << out.EntityStatus;
    }
};