#pragma once

#include "../types/SocketPrimitives.h"

struct SBNBTEntityReq {
    static const int Id = 0x0D;

    SocketVarInt TransactionId;
    SocketVarInt EntityId;

    friend SocketIStream& operator>>(SocketIStream& sock, SBNBTEntityReq& out) {
        return sock
            >> out.TransactionId
            >> out.EntityId;
    }
};