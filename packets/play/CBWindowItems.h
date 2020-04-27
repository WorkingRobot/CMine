#pragma once

#include "../types/SocketPrimitives.h"

struct CBWindowItems {
    static const int Id = 0x15;

    SocketUByte WindowId;
    std::vector<SocketSlot> SlotData;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBWindowItems& out) {
        sock << out.WindowId << SocketVarInt(out.SlotData.size());
        for (auto& slot : out.SlotData) {
            sock << slot;
        }
        return sock;
    }
};