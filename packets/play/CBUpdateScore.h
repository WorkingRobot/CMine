#pragma once

#include "../types/SocketPrimitives.h"

struct CBUpdateScore {
    const int Id = 0x4D;

    SocketString EntityName; // username (player) or uuid (entity)
    SocketByte Action; // 0: create/update, 1: remove
    SocketString ObjName;
    std::optional<SocketVarInt> Value;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBUpdateScore& out) {
        sock
            << out.EntityName
            << out.Action
            << out.ObjName;
        if (out.Action != 1) {
            sock << out.Value.value();
        }
        return sock;
    }
};