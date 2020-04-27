#pragma once

#include "../types/SocketPrimitives.h"

struct SBWindowClick {
    static const int Id = 0x09;

    SocketUByte WindowId;
    SocketShort Slot;
    SocketByte Button;
    SocketShort Action;
    SocketVarInt Mode; // 0-6
    SocketSlot ClickedItem;

    friend SocketIStream& operator>>(SocketIStream& sock, SBWindowClick& out) {
        return sock
            >> out.WindowId
            >> out.Slot
            >> out.Button
            >> out.Action
            >> out.Mode
            >> out.ClickedItem;
    }
};