#pragma once

#include "../types/SocketPrimitives.h"

struct CBEntityMetadata {
    static const int Id = 0x44;

    SocketVarInt EntityId;
    SocketEntityMetadata Metadata; // too lazy to implement

    friend SocketOStream& operator<<(SocketOStream& sock, const CBEntityMetadata& out) {
        return sock
            << out.EntityId
            << out.Metadata;
    }
};