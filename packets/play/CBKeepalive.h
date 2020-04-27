#pragma once

#include "../types/SocketPrimitives.h"

struct CBKeepalive {
    static const int Id = 0x21;

    SocketLong KeepaliveId; // normal servers use epoch milliseconds

    friend SocketOStream& operator<<(SocketOStream& sock, const CBKeepalive& out) {
        return sock
            << out.KeepaliveId;
    }
};