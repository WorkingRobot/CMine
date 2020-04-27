#pragma once

#include "../types/SocketPrimitives.h"

struct CBRespawn {
    static const int Id = 0x3B;

    SocketInt Dimension;
    SocketLong HashedSeed;
    SocketUByte Gamemode;
    SocketString LevelType;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBRespawn& out) {
        return sock
            << out.Dimension
            << out.HashedSeed
            << out.Gamemode
            << out.LevelType;
    }
};