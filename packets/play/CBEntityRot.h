#pragma once

#include "../types/SocketPrimitives.h"

struct CBEntityRot {
    static const int Id = 0x2B;

    SocketVarInt EntityId;
    SocketAngle Yaw; // absolute, not deltas
    SocketAngle Pitch;
    SocketBool OnGround;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBEntityRot& out) {
        return sock
            << out.EntityId
            << out.Yaw << out.Pitch
            << out.OnGround;
    }
};