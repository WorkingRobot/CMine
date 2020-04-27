#pragma once

#include "../types/SocketPrimitives.h"

struct SBPluginMessage {
    static const int Id = 0x0B;

    SocketIdentifier Channel;
    SocketString Data; // maybe SocketByteArray would be smarter?

    friend SocketIStream& operator>>(SocketIStream& sock, SBPluginMessage& out) {
        return sock
            >> out.Channel
            >> out.Data;
    }
};