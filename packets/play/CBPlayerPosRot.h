#pragma once

#include "../types/SocketPrimitives.h"

struct CBPlayerPosRot {
    const int Id = 0x36;

    SocketDouble PosX;
    SocketDouble PosY;
    SocketDouble PosZ;
    SocketFloat Yaw;
    SocketFloat Pitch;
    SocketByte Flags;
    SocketVarInt TeleportId;


    friend SocketOStream& operator<<(SocketOStream& sock, const CBPlayerPosRot& out) {
        return sock
            << out.PosX << out.PosY << out.PosZ
            << out.Yaw << out.Pitch
            << out.Flags
            << out.TeleportId;
    }
};