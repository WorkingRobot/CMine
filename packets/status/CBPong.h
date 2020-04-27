#pragma once

#include "../types/SocketPrimitives.h"

struct CBPong {
    SocketLong Payload;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBPong& out) {
        return sock << out.Payload;
    }
};