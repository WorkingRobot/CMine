#pragma once

#include "../types/SocketPrimitives.h"

struct CBLoginDisconnect {
    SocketChat Reason;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBLoginDisconnect& out) {
        return sock << out.Reason;
    }
};