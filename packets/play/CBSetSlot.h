#pragma once

#include "../types/SocketPrimitives.h"

struct CBSetSlot {
    const int Id = 0x17;

    SocketUByte WindowId;
    SocketShort Slot;
    SocketSlot SlotData;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBSetSlot& out) {
        return sock
            << out.WindowId
            << out.Slot
            << out.SlotData;
    }
};