#pragma once

#include "../types/SocketPrimitives.h"

struct SBWindowClose {
    static const int Id = 0x0A;

    SocketUByte WindowId;

    friend SocketIStream& operator>>(SocketIStream& sock, SBWindowClose& out) {
        return sock
            >> out.WindowId;
    }
};