#pragma once

#include "../types/SocketPrimitives.h"

struct CBEntityEquipment {
    const int Id = 0x47;

    SocketVarInt EntityId;
    SocketVarInt Slot; // 0: main hand, 1: off hand, 2-5: armor (boots->helmet)
    SocketSlot Item;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBEntityEquipment& out) {
        return sock
            << out.EntityId
            << out.Slot
            << out.Item;
    }
};