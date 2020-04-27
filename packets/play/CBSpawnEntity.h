#pragma once

#include "../types/SocketPrimitives.h"

struct CBSpawnEntity {
    const int Id = 0x00;

    SocketVarInt EntityId;
    SocketGUID ObjectUuid;
    SocketVarInt Type;
    SocketDouble X;
    SocketDouble Y;
    SocketDouble Z;
    SocketAngle Pitch;
    SocketAngle Yaw;
    SocketInt Data;
    SocketShort VelX;
    SocketShort VelY;
    SocketShort VelZ;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBSpawnEntity& out) {
        return sock
            << out.EntityId
            << out.ObjectUuid
            << out.Type
            << out.X << out.Y << out.Z
            << out.Pitch << out.Yaw
            << out.Data
            << out.VelX << out.VelY << out.VelZ;
    }
};