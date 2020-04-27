#pragma once

#include "../types/SocketPrimitives.h"

struct CBJoinGame {
    const int Id = 0x26;

    SocketInt EntityId;
    SocketUByte Gamemode;
    SocketInt Dimension; // -1: nether, 0: overworld, 1: end
    SocketLong HashedSeed; // first 8 bytes of SHA-256 of world seed
    SocketUByte MaxPlayer; // obsolete
    SocketString LevelType; // enum
    SocketVarInt ViewDistance; // 2-32
    SocketBool ReducedDebugInfo;
    SocketBool EnableRespawnScreen;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBJoinGame& out) {
        return sock
            << out.EntityId
            << out.Gamemode
            << out.Dimension
            << out.HashedSeed
            << out.MaxPlayer
            << out.LevelType
            << out.ViewDistance
            << out.ReducedDebugInfo
            << out.EnableRespawnScreen;
    }
};