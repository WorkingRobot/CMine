#pragma once

#include "../types/SocketPrimitives.h"

struct SBPlayerPosRot {
    static const int Id = 0x12;

    SocketDouble PosX;
    SocketDouble FeetY;
    SocketDouble PosZ;
    SocketFloat Yaw;
    SocketFloat Pitch;
    SocketBool OnGround;

    friend SocketIStream& operator>>(SocketIStream& sock, SBPlayerPosRot& out) {
        return sock
            >> out.PosX >> out.FeetY >> out.PosZ
            >> out.Yaw >> out.Pitch
            >> out.OnGround;
    }
};