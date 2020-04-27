#pragma once

#include "../types/SocketPrimitives.h"

struct SBAnimation {
    static const int Id = 0x2A;

    SocketVarInt Hand; // 0: main hand, 1: off hand

    friend SocketIStream& operator>>(SocketIStream& sock, SBAnimation& out) {
        return sock
            >> out.Hand;
    }
};