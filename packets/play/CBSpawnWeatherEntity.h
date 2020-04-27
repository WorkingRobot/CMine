#pragma once

#include "../types/SocketPrimitives.h"

struct CBSpawnWeatherEntity {
    const int Id = 0x02;

    SocketVarInt EntityId;
    SocketByte Type; // Enum, always 1 for thunderbolt tho
    SocketDouble X;
    SocketDouble Y;
    SocketDouble Z;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBSpawnWeatherEntity& out) {
        return sock
            << out.EntityId
            << out.Type
            << out.X << out.Y << out.Z;
    }
};