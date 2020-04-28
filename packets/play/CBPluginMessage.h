#pragma once

#include "../types/SocketPrimitives.h"

struct CBPluginMessage {
    static const int Id = 0x19;

    SocketIdentifier Channel;
    SocketPluginMessage Data;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBPluginMessage& out) {
        return sock
            << out.Channel
            << out.Data;
    }
};