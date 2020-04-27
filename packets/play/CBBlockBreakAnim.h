#pragma once

#include "../types/SocketPrimitives.h"

struct CBBlockBreakAnim {
    static const int Id = 0x09;

    SocketVarInt EntityId;
    SocketPosition Location;
    SocketByte DestroyStage; // 0-9, other value removes

    friend SocketOStream& operator<<(SocketOStream& sock, const CBBlockBreakAnim& out) {
        return sock
            << out.EntityId
            << out.Location
            << out.DestroyStage;
    }
};