#pragma once

#include "../types/SocketPrimitives.h"

struct CBSpawnLivingEntity {
    static const int Id = 0x03;

    SocketVarInt EntityId;
    SocketGUID EntityUuid;
    SocketVarInt Type;
    SocketDouble X;
    SocketDouble Y;
    SocketDouble Z;
    SocketAngle Yaw;
    SocketAngle Pitch;
    SocketAngle HeadPitch;
    SocketShort VelX;
    SocketShort VelY;
    SocketShort VelZ;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBSpawnLivingEntity& out) {
        return sock
            << out.EntityId
            << out.EntityUuid
            << out.Type
            << out.X << out.Y << out.Z
            << out.Yaw << out.Pitch << out.HeadPitch
            << out.VelX << out.VelY << out.VelZ;
    }
};