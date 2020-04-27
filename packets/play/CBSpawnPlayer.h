#pragma once

#include "../types/SocketPrimitives.h"

struct CBSpawnPlayer {
    static const int Id = 0x05;

    SocketVarInt EntityId;
    SocketGUID PlayerUuid;
    SocketDouble X;
    SocketDouble Y;
    SocketDouble Z;
    SocketAngle Yaw;
    SocketAngle Pitch;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBSpawnPlayer& out) {
        return sock
            << out.EntityId
            << out.PlayerUuid
            << out.X << out.Y << out.Z
            << out.Yaw << out.Pitch;
    }
};