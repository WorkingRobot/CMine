#pragma once

#include "../types/SocketPrimitives.h"

struct SBUpdateSign {
    static const int Id = 0x29;

    SocketPosition Location;
    SocketString Line1;
    SocketString Line2;
    SocketString Line3;
    SocketString Line4;

    friend SocketIStream& operator>>(SocketIStream& sock, SBUpdateSign& out) {
        return sock
            >> out.Location
            >> out.Line1
            >> out.Line2
            >> out.Line3
            >> out.Line4;
    }
};