#pragma once

#include "../types/SocketPrimitives.h"

struct CBVehicleMove {
    const int Id = 0x2D;

    // all absolute values
    SocketDouble PosX;
    SocketDouble PosY;
    SocketDouble PosZ;
    SocketFloat Yaw;
    SocketFloat Pitch;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBVehicleMove& out) {
        return sock
            << out.PosX << out.PosY << out.PosZ
            << out.Yaw << out.Pitch;
    }
};