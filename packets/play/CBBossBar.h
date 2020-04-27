#pragma once

#include "../types/SocketPrimitives.h"

struct CBBossBar {
    static const int Id = 0x0D;

    SocketGUID Uuid;
    SocketVarInt Action; // enum

    // 0: add
    SocketChat Title;
    SocketFloat Health; // 0 - 1 (can go above, though)
    SocketVarInt Color; // 0-6
    SocketVarInt Division; // 0-4
    SocketByte Flags; // 0x1, 0x2, 0x4

    // 1: remove
    // nothing

    // 2: update health
    // Health

    // 3: update title
    // Title

    // 4: update style
    // Color
    // Division

    // 5: update flags
    // Flags

    friend SocketOStream& operator<<(SocketOStream& sock, const CBBossBar& out) {
        sock << out.Uuid << out.Action;
        switch (out.Action)
        {
        case 0:
            return sock
                << out.Title
                << out.Health
                << out.Color
                << out.Division
                << out.Flags;
        case 1:
            return sock;
        case 2:
            return sock << out.Health;
        case 3:
            return sock << out.Title;
        case 4:
            return sock << out.Color << out.Division;
        case 5:
            return sock << out.Flags;
        }
    }
};