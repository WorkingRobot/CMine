#pragma once

#include "../types/SocketPrimitives.h"

struct CBOpenHorseWindow {
    static const int Id = 0x20;

    SocketUByte WindowId; // a ton of oddball reasons
    SocketVarInt SlotCount;
    SocketVarInt EntityId; // might be wrong (could be SocketInt)

    friend SocketOStream& operator<<(SocketOStream& sock, const CBOpenHorseWindow& out) {
        return sock
            << out.WindowId
            << out.SlotCount
            << out.EntityId;
    }
};