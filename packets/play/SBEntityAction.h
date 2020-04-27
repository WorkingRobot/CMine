#pragma once

#include "../types/SocketPrimitives.h"

struct SBEntityAction {
    static const int Id = 0x1B;

    SocketVarInt EntityId;
    SocketVarInt Action; // 0-8
    SocketVarInt JumpBoost; // used in start jump with horse (ranges 0-100, otherwise 0)

    friend SocketIStream& operator>>(SocketIStream& sock, SBEntityAction& out) {
        return sock
            >> out.EntityId
            >> out.Action
            >> out.JumpBoost;
    }
};