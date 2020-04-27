#pragma once

#include "../types/SocketPrimitives.h"

struct SBSelectTrade {
    static const int Id = 0x21;

    SocketVarInt SelectedSlot;

    friend SocketIStream& operator>>(SocketIStream& sock, SBSelectTrade& out) {
        return sock
            >> out.SelectedSlot;
    }
};