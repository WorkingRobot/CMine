#pragma once

#include "../types/SocketPrimitives.h"

struct SBVehicleMove {
    static const int Id = 0x15;

    SocketDouble PosX;
    SocketDouble PosY;
    SocketDouble PosZ;
    SocketFloat Yaw;
    SocketFloat Pitch;

    friend SocketIStream& operator>>(SocketIStream& sock, SBVehicleMove& out) {
        return sock
            >> out.PosX >> out.PosY >> out.PosZ
            >> out.Yaw >> out.Pitch;
    }
};