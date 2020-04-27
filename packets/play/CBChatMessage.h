#pragma once

#include "../types/SocketPrimitives.h"

struct CBChatMessage {
    static const int Id = 0x0F;

    SocketChat Data; // 32k bytes max
    SocketByte Position; // 0 chat, 1 system, 2 game info (actionbar)

    friend SocketOStream& operator<<(SocketOStream& sock, const CBChatMessage& out) {
        return sock
            << out.Data
            << out.Position;
    }
};