#pragma once

#include "../types/SocketPrimitives.h"

struct CBResourcePackSend {
    const int Id = 0x3A;

    SocketString Url;
    SocketString Hash;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBResourcePackSend& out) {
        return sock
            << out.Url
            << out.Hash;
    }
};