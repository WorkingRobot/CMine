#pragma once

#include "../types/SocketPrimitives.h"

struct CBWindowClose {
    static const int Id = 0x14;

    SocketUByte WindowId;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBWindowClose& out) {
        return sock
            << out.WindowId;
    }
};