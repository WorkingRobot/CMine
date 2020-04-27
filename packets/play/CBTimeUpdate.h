#pragma once

#include "../types/SocketPrimitives.h"

struct CBTimeUpdate {
    static const int Id = 0x4F;

    SocketLong WorldAge;
    SocketLong TimeOfDay;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBTimeUpdate& out) {
        return sock
            << out.WorldAge
            << out.TimeOfDay;
    }
};