#pragma once

#include "../types/SocketPrimitives.h"

struct SBSteerBoat {
    static const int Id = 0x16;

    SocketBool LeftPaddle;
    SocketBool RightPaddle;

    friend SocketIStream& operator>>(SocketIStream& sock, SBSteerBoat& out) {
        return sock
            >> out.LeftPaddle
            >> out.RightPaddle;
    }
};