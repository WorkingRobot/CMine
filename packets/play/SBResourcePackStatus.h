#pragma once

#include "../types/SocketPrimitives.h"

struct SBResourcePackStatus {
    static const int Id = 0x1F;

    SocketVarInt Result; // 0: loaded, 1: declined, 2: failed download, 3: accepted

    friend SocketIStream& operator>>(SocketIStream& sock, SBResourcePackStatus& out) {
        return sock
            >> out.Result;
    }
};