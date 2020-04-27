#pragma once

#include "../types/SocketPrimitives.h"

struct CBWorldBorder {
    const int Id = 0x3E;

    SocketVarInt Action;

    SocketDouble PosX;
    SocketDouble PosZ;
    SocketDouble OldDiameter;
    SocketDouble NewDiameter;
    SocketVarLong Speed;
    SocketVarInt PortalTpBoundary;
    SocketVarInt WarningTime;
    SocketVarInt WarningBlocks;

    // 0: set size
    // NewDiameter

    // 1: lerp size
    // OldDiameter
    // NewDiameter
    // Speed

    // 2: set center
    // PosX
    // PosZ

    // 3: initialize
    // all of em

    // 4: set warning time
    // WarningTime

    // 5: set warning blocks
    // WarningBlocks

    friend SocketOStream& operator<<(SocketOStream& sock, const CBWorldBorder& out) {
        sock << out.Action;
        switch (out.Action)
        {
        case 0:
            sock
                << out.NewDiameter;
            break;
        case 1:
            sock
                << out.OldDiameter
                << out.NewDiameter
                << out.Speed;
            break;
        case 2:
            sock
                << out.PosX << out.PosZ;
            break;
        case 3:
            sock
                << out.PosX << out.PosZ
                << out.OldDiameter
                << out.NewDiameter
                << out.Speed
                << out.PortalTpBoundary
                << out.WarningTime
                << out.WarningBlocks;
            break;
        case 4:
            sock
                << out.WarningTime;
            break;
        case 5:
            sock
                << out.WarningBlocks;
            break;
        }
        return sock;
    }
};