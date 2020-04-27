#pragma once

#include "../types/SocketPrimitives.h"

struct CBEntityTeleport {
    const int Id = 0x57;

    SocketVarInt EntityId;
    SocketDouble PosX;
    SocketDouble PosY;
    SocketDouble PosZ;
    SocketAngle Yaw;
    SocketAngle Pitch;
    SocketBool OnGround;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBEntityTeleport& out) {
        return sock
            << out.EntityId
            << out.PosX << out.PosY << out.PosZ
            << out.Yaw << out.Pitch
            << out.OnGround;
    }
};