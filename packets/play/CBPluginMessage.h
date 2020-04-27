#pragma once

#include "../types/SocketPrimitives.h"

struct CBPluginMessage {
    const int Id = 0x19;

    SocketIdentifier Channel;
    SocketString Data; // maybe SocketByteArray would be smarter?

    friend SocketOStream& operator<<(SocketOStream& sock, const CBPluginMessage& out) {
        return sock
            << out.Channel
            << out.Data;
    }
};