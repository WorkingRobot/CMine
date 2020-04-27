#pragma once

#include "../types/SocketPrimitives.h"

struct SBPlayerRot {
    static const int Id = 0x13;

    SocketFloat Yaw;
    SocketFloat Pitch;
    SocketBool OnGround;

    friend SocketIStream& operator>>(SocketIStream& sock, SBPlayerRot& out) {
        return sock
            >> out.Yaw >> out.Pitch
            >> out.OnGround;
    }
};