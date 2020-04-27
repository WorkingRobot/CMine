#pragma once

#include "../types/SocketPrimitives.h"

struct SBKeepalive {
    static const int Id = 0x0F;

    SocketLong KeepaliveId;

    friend SocketIStream& operator>>(SocketIStream& sock, SBKeepalive& out) {
        return sock
            >> out.KeepaliveId;
    }
};