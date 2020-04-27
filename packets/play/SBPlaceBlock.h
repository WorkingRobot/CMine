#pragma once

#include "../types/SocketPrimitives.h"

struct SBPlaceBlock {
    static const int Id = 0x2C;

    SocketVarInt Hand;
    SocketPosition Position;
    SocketVarInt Face;
    SocketFloat CurPosX;
    SocketFloat CurPosY;
    SocketFloat CurPosZ;
    SocketBool InsideBlock;

    friend SocketIStream& operator>>(SocketIStream& sock, SBPlaceBlock& out) {
        return sock
            >> out.Hand
            >> out.Position
            >> out.Face
            >> out.CurPosX >> out.CurPosY >> out.CurPosZ
            >> out.InsideBlock;
    }
};