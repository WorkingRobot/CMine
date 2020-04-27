#pragma once

#include "../types/SocketPrimitives.h"

struct CBEntityPos {
    static const int Id = 0x29;

    SocketVarInt EntityId;
    SocketShort DeltaX; // allows movement in at most 8 blocks in any coordinate direction
    SocketShort DeltaY; // = (currentPos * 32 - prevPos * 32) * 128 
    SocketShort DeltaZ;
    SocketBool OnGround;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBEntityPos& out) {
        return sock
            << out.EntityId
            << out.DeltaX << out.DeltaY << out.DeltaZ
            << out.OnGround;
    }
};