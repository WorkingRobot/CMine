#pragma once

#include "../types/SocketPrimitives.h"

struct SBNameItem {
    static const int Id = 0x1E;

    SocketString ItemName;

    friend SocketIStream& operator>>(SocketIStream& sock, SBNameItem& out) {
        return sock
            >> out.ItemName;
    }
};