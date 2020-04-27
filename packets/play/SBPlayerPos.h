#pragma once

#include "../types/SocketPrimitives.h"

struct SBPlayerPos {
    static const int Id = 0x11;

    SocketDouble PosX;
    SocketDouble FeetY;
    SocketDouble PosZ;
    SocketBool OnGround;

    friend SocketIStream& operator>>(SocketIStream& sock, SBPlayerPos& out) {
        return sock
            >> out.PosX >> out.FeetY >> out.PosZ
            >> out.OnGround;
    }
};