#pragma once

#include "../types/SocketPrimitives.h"

struct CBDestroyEntities {
    static const int Id = 0x38;

    std::vector<SocketVarInt> EntityIds;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBDestroyEntities& out) {
        sock << SocketVarInt(out.EntityIds.size());
        for (auto& id : out.EntityIds) {
            sock << id;
        }
    }
};