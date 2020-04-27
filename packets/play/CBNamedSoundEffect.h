#pragma once

#include "../types/SocketPrimitives.h"

struct CBNamedSoundEffect {
    const int Id = 0x1A;

    SocketIdentifier SoundName;
    SocketVarInt SoundCategory; // enum
    SocketInt PosX;
    SocketInt PosY; // these are "multiplied by 8 (fixed-point number with only 3 bits dedicated to the fractional part)"
    SocketInt PosZ;
    SocketFloat Volume;
    SocketFloat Pitch; // 0.5 - 2.0

    friend SocketOStream& operator<<(SocketOStream& sock, const CBNamedSoundEffect& out) {
        return sock
            << out.SoundName
            << out.SoundCategory
            << out.PosX << out.PosY << out.PosZ
            << out.Volume
            << out.Pitch;
    }
};