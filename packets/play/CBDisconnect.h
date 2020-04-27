#pragma once

#include "../types/SocketPrimitives.h"

struct CBDisconnect {
    const int Id = 0x1B;

    SocketChat Reason;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBDisconnect& out) {
        return sock
            << out.Reason;
    }
};