#pragma once

#include "../types/SocketPrimitives.h"

struct SBPing {
    SocketLong Payload;

    friend SocketIStream& operator>>(SocketIStream& sock, SBPing& out) {
        sock >> out.Payload;
        return sock;
    }
};