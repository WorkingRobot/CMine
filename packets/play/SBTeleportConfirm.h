#pragma once

#include "../types/SocketPrimitives.h"

struct SBTeleportConfirm {
    static const int Id = 0x00;

    SocketVarInt TeleportId;

    friend SocketIStream& operator>>(SocketIStream& sock, SBTeleportConfirm& out) {
        return sock
            >> out.TeleportId;
    }
};