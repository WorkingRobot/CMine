#pragma once

#include "../types/SocketPrimitives.h"

struct SBClientStatus {
    static const int Id = 0x04;

    SocketVarInt ActionId; // 0: perform respawn, 1: request stats

    friend SocketIStream& operator>>(SocketIStream& sock, SBClientStatus& out) {
        return sock
            >> out.ActionId;
    }
};