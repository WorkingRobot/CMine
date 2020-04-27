#pragma once

#include "../types/SocketPrimitives.h"

struct CBEntityHeadLook {
    const int Id = 0x3C;

    SocketVarInt EntityId;
    SocketAngle HeadYaw; // absolute, not delta

    friend SocketOStream& operator<<(SocketOStream& sock, const CBEntityHeadLook& out) {
        return sock
            << out.EntityId
            << out.HeadYaw;
    }
};