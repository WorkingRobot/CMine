#pragma once

#include "../types/SocketPrimitives.h"

struct CBHeldItemChange {
    static const int Id = 0x40;

    SocketByte Slot; // 0-8

    friend SocketOStream& operator<<(SocketOStream& sock, const CBHeldItemChange& out) {
        return sock
            << out.Slot;
    }
};