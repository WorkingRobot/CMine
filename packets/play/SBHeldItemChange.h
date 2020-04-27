#pragma once

#include "../types/SocketPrimitives.h"

struct SBHeldItemChange {
    static const int Id = 0x23;

    SocketShort Slot;

    friend SocketIStream& operator>>(SocketIStream& sock, SBHeldItemChange& out) {
        return sock
            >> out.Slot;
    }
};