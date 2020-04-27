#pragma once

#include "../types/SocketPrimitives.h"

struct CBLoginSuccess {
    SocketString UUID; // Unlike in other packets, this field contains the UUID as a string with hyphens.
    SocketString Username;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBLoginSuccess& out) {
        return sock << out.UUID << out.Username;
    }
};