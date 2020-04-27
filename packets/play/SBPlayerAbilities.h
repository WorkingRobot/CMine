#pragma once

#include "../types/SocketPrimitives.h"

struct SBPlayerAbilities {
    static const int Id = 0x19;

    SocketByte Flags; // 0x08: god mode, 0x04: can fly, 0x02: is flying, 0x01: is creative
    SocketFloat FlySpeed;
    SocketFloat WalkSpeed;

    friend SocketIStream& operator>>(SocketIStream& sock, SBPlayerAbilities& out) {
        return sock
            >> out.Flags
            >> out.FlySpeed
            >> out.WalkSpeed;
    }
};