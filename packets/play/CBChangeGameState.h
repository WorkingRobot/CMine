#pragma once

#include "../types/SocketPrimitives.h"

struct CBChangeGameState {
    const int Id = 0x1F;

    SocketUByte Reason; // a ton of oddball reasons
    SocketFloat Value;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBChangeGameState& out) {
        return sock
            << out.Reason
            << out.Value;
    }
};