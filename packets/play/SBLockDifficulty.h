#pragma once

#include "../types/SocketPrimitives.h"

struct SBLockDifficulty {
    static const int Id = 0x10;

    SocketBool Locked;

    friend SocketIStream& operator>>(SocketIStream& sock, SBLockDifficulty& out) {
        return sock
            >> out.Locked;
    }
};