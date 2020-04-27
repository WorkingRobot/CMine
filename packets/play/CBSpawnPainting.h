#pragma once

#include "../types/SocketPrimitives.h"

struct CBSpawnPainting {
    static const int Id = 0x04;

    SocketVarInt EntityId;
    SocketGUID EntityUuid;
    SocketVarInt Motive;
    SocketPosition Location;
    SocketByte Direction; // south 0, west 1, north 2, east 3

    friend SocketOStream& operator<<(SocketOStream& sock, const CBSpawnPainting& out) {
        return sock
            << out.EntityId
            << out.EntityUuid
            << out.Motive
            << out.Location
            << out.Direction;
    }
};