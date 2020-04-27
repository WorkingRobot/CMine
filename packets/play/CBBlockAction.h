#pragma once

#include "../types/SocketPrimitives.h"

struct CBBlockAction {
    static const int Id = 0x0B;

    SocketPosition Location;
    SocketByte ActionId;
    SocketByte ActionParam;
    SocketVarInt BlockType;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBBlockAction& out) {
        return sock
            << out.Location
            << out.ActionId
            << out.ActionParam
            << out.BlockType;
    }
};