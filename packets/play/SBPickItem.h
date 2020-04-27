#pragma once

#include "../types/SocketPrimitives.h"

struct SBPickItem {
    static const int Id = 0x17;

    SocketVarInt Slot;

    friend SocketIStream& operator>>(SocketIStream& sock, SBPickItem& out) {
        return sock
            >> out.Slot;
    }
};