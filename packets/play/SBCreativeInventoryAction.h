#pragma once

#include "../types/SocketPrimitives.h"

struct SBCreativeInventoryAction {
    static const int Id = 0x26;

    SocketShort Slot;
    SocketSlot ClickedItem;

    friend SocketIStream& operator>>(SocketIStream& sock, SBCreativeInventoryAction& out) {
        return sock
            >> out.Slot
            >> out.ClickedItem;
    }
};