#pragma once

#include "../types/SocketPrimitives.h"

struct CBEntityPosRot {
    const int Id = 0x2A;

    SocketVarInt EntityId;
    SocketShort DeltaX; // allows movement in at most 8 blocks in any coordinate direction
    SocketShort DeltaY; // = (currentPos * 32 - prevPos * 32) * 128 
    SocketShort DeltaZ;
    SocketAngle Yaw; // absolute, not deltas
    SocketAngle Pitch;
    SocketBool OnGround;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBEntityPosRot& out) {
        return sock
            << out.EntityId
            << out.DeltaX << out.DeltaY << out.DeltaZ
            << out.Yaw << out.Pitch
            << out.OnGround;
    }
};