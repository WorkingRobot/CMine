#pragma once

#include "../types/SocketPrimitives.h"

struct SBWindowClickButton {
    static const int Id = 0x08;

    SocketByte WindowId;
    SocketByte ButtonId;

    friend SocketIStream& operator>>(SocketIStream& sock, SBWindowClickButton& out) {
        return sock
            >> out.WindowId
            >> out.ButtonId;
    }
};