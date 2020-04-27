#pragma once

#include "../types/SocketPrimitives.h"

struct SBSteerVehicle {
    static const int Id = 0x1C;

    SocketFloat Sideways; // +: left, -: right
    SocketFloat Forward; // +: forward, -: backward
    SocketUByte Flags; // 0x1: jump, 0x2: unmount

    friend SocketIStream& operator>>(SocketIStream& sock, SBSteerVehicle& out) {
        return sock
            >> out.Sideways
            >> out.Forward
            >> out.Flags;
    }
};