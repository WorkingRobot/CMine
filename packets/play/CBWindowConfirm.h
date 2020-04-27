#pragma once

#include "../types/SocketPrimitives.h"

struct CBWindowConfirm {
    const int Id = 0x13;

    SocketUByte WindowId;
    SocketShort ActionNum;
    SocketBool Accepted;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBWindowConfirm& out) {
        return sock
            << out.WindowId
            << out.ActionNum
            << out.Accepted;
    }
};