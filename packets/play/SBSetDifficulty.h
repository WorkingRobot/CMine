#pragma once

#include "../types/SocketPrimitives.h"

struct SBSetDifficulty {
    static const int Id = 0x02;

    SocketByte Difficulty;

    friend SocketIStream& operator>>(SocketIStream& sock, SBSetDifficulty& out) {
        return sock
            >> out.Difficulty;
    }
};