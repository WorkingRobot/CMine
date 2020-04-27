#pragma once

#include "../types/SocketPrimitives.h"

struct CBSetCompr {
    SocketVarInt Threshold; // Maximum size of a packet before it is compressed

    friend SocketOStream& operator<<(SocketOStream& sock, const CBSetCompr& out) {
        return sock << out.Threshold;
    }
};