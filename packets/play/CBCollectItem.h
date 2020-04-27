#pragma once

#include "../types/SocketPrimitives.h"

struct CBCollectItem {
    static const int Id = 0x56;

    SocketVarInt CollectedId;
    SocketVarInt CollectorId;
    SocketVarInt PickupCount; // always 1 for xp orbs though

    friend SocketOStream& operator<<(SocketOStream& sock, const CBCollectItem& out) {
        return sock
            << out.CollectedId
            << out.CollectorId
            << out.PickupCount;
    }
};