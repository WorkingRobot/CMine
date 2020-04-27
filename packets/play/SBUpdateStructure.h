#pragma once

#include "../types/SocketPrimitives.h"

struct SBUpdateStructure {
    static const int Id = 0x28;

    SocketPosition Location;
    SocketVarInt Action; // 0: update data, 1: save structure, 2: load structure, 3: detect size
    SocketVarInt Mode; // 0: save, 1: load, 2: corner, 3: data
    SocketString Name;
    SocketByte OffX;
    SocketByte OffY; // -32 - 32
    SocketByte OffZ;
    SocketByte SizeX;
    SocketByte SizeY; // 0-32
    SocketByte SizeZ;
    SocketVarInt Mirror; // 0: none, 1: left-right, 2: front-back
    SocketVarInt Rotation; // (clockwise) 0: none, 1: 90, 2: 180, 3: 270
    SocketString Metadata;
    SocketFloat Integrity; // 0-1
    SocketVarLong Seed;
    SocketByte Flags; // 0x1: ignore entities, 0x2: show air, 0x4: show bounding box

    friend SocketIStream& operator>>(SocketIStream& sock, SBUpdateStructure& out) {
        return sock
            >> out.Location
            >> out.Action
            >> out.Mode
            >> out.Name
            >> out.OffX >> out.OffY >> out.OffZ
            >> out.SizeX >> out.SizeY >> out.SizeZ
            >> out.Mirror
            >> out.Rotation
            >> out.Metadata
            >> out.Integrity
            >> out.Seed
            >> out.Flags;
    }
};