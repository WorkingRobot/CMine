#pragma once

#include "../types/SocketPrimitives.h"

struct CBBlockEntityData {
    static const int Id = 0x0A;

    SocketPosition Location;
    SocketByte Action;
    SocketNBT NbtData;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBBlockEntityData& out) {
        return sock
            << out.Location
            << out.Action
            << out.NbtData;
    }
};