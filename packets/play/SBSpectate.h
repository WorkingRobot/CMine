#pragma once

#include "../types/SocketPrimitives.h"

struct SBSpectate {
    static const int Id = 0x2B;

    SocketGUID TargetPlayer;

    friend SocketIStream& operator>>(SocketIStream& sock, SBSpectate& out) {
        return sock
            >> out.TargetPlayer;
    }
};