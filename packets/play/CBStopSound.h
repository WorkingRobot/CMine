#pragma once

#include "../types/SocketPrimitives.h"

struct CBStopSound {
    static const int Id = 0x53;

    SocketByte Flags;
    std::optional<SocketVarInt> Source; // bitmask 0x1
    std::optional<SocketIdentifier> Sound; // bitmask 0x2

    friend SocketOStream& operator<<(SocketOStream& sock, const CBStopSound& out) {
        sock << out.Flags;
        if (out.Flags & 0x1) {
            sock << out.Source.value();
        }
        if (out.Flags & 0x2) {
            sock << out.Sound.value();
        }
        return sock;
    }
};