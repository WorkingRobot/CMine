#pragma once

#include "../types/SocketPrimitives.h"

struct SBChatMessage {
    static const int Id = 0x03;

    SocketString Message;

    friend SocketIStream& operator>>(SocketIStream& sock, SBChatMessage& out) {
        return sock
            >> out.Message;
    }
};