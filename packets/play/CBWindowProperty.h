#pragma once

#include "../types/SocketPrimitives.h"

struct CBWindowProperty {
    const int Id = 0x16;

    SocketUByte WindowId;
    SocketShort Property;
    SocketShort Value;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBWindowProperty& out) {
        return sock
            << out.WindowId
            << out.Property
            << out.Value;
    }
};