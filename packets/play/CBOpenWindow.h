#pragma once

#include "../types/SocketPrimitives.h"

struct CBOpenWindow {
    const int Id = 0x2F;

    SocketVarInt WindowId;
    SocketVarInt WindowType;
    SocketChat WindowTitle;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBOpenWindow& out) {
        return sock
            << out.WindowId
            << out.WindowType
            << out.WindowTitle;
    }
};