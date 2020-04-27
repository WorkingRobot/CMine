#pragma once

#include "../types/SocketPrimitives.h"

struct CBAckPlayerDig {
    static const int Id = 0x08;

    SocketPosition Location;
    SocketVarInt Block; // current block state
    SocketVarInt Status; // 0 started, 1 cancelled, 2 finished
    SocketBool Success; // true if succeeded, false if client should undo local work

    friend SocketOStream& operator<<(SocketOStream& sock, const CBAckPlayerDig& out) {
        return sock
            << out.Location
            << out.Block
            << out.Status
            << out.Success;
    }
};