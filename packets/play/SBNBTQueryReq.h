#pragma once

#include "../types/SocketPrimitives.h"

struct SBNBTQueryReq {
    static const int Id = 0x01;

    SocketVarInt TransactionId;
    SocketPosition Location;

    friend SocketIStream& operator>>(SocketIStream& sock, SBNBTQueryReq& out) {
        return sock
            >> out.TransactionId
            >> out.Location;
    }
};