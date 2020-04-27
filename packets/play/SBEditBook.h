#pragma once

#include "../types/SocketPrimitives.h"

struct SBEditBook {
    static const int Id = 0x0C;

    SocketSlot Book;
    SocketBool Signing; // true if signing, false if saving as draft
    SocketVarInt Hand; // 0: main hand, 1: off hand

    friend SocketIStream& operator>>(SocketIStream& sock, SBEditBook& out) {
        return sock
            >> out.Book
            >> out.Signing
            >> out.Hand;
    }
};