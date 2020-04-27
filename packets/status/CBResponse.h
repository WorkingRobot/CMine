#pragma once

#include "../types/SocketPrimitives.h"

struct CBResponse {
    SocketVarInt JsonLength;
    SocketString JsonString;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBResponse& out) {
        return sock << out.JsonString;
    }
};