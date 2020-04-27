#pragma once

#include "../types/SocketPrimitives.h"

struct SBUseItem {
    static const int Id = 0x2D;

    SocketVarInt Hand; // 0: main hand, 1: off hand

    friend SocketIStream& operator>>(SocketIStream& sock, SBUseItem& out) {
        return sock
            >> out.Hand;
    }
};