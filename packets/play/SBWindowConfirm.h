#pragma once

#include "../types/SocketPrimitives.h"

struct SBWindowConfirm {
    static const int Id = 0x07;

    SocketByte WindowId;
    SocketShort Action;
    SocketBool Accepted;

    friend SocketIStream& operator>>(SocketIStream& sock, SBWindowConfirm& out) {
        return sock
            >> out.WindowId
            >> out.Action
            >> out.Accepted;
    }
};