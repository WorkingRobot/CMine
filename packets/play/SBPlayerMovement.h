#pragma once

#include "../types/SocketPrimitives.h"

struct SBPlayerMovement {
    static const int Id = 0x14;

    SocketBool OnGround;

    friend SocketIStream& operator>>(SocketIStream& sock, SBPlayerMovement& out) {
        return sock
            >> out.OnGround;
    }
};