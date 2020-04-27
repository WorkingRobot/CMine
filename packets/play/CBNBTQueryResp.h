#pragma once

#include "../types/SocketPrimitives.h"

struct CBNBTQueryResp {
    static const int Id = 0x55;

    SocketVarInt TransactionId;
    SocketNBT Data;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBNBTQueryResp& out) {
        return sock
            << out.TransactionId
            << out.Data;
    }
};