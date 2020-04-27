#pragma once

#include "../types/SocketPrimitives.h"

struct SBTabComplete {
    static const int Id = 0x06;

    SocketVarInt TransactionId;
    SocketString Text;

    friend SocketIStream& operator>>(SocketIStream& sock, SBTabComplete& out) {
        return sock
            >> out.TransactionId
            >> out.Text;
    }
};