#pragma once

#include "../types/SocketPrimitives.h"

struct CBSoundEffect {
    static const int Id = 0x52;

    SocketVarInt SoundId;
    SocketVarInt SoundCategory;
    SocketInt PosX;
    SocketInt PosY; // divide by 8 to get actual position
    SocketInt PosZ;
    SocketFloat Volume;
    SocketFloat Pitch;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBSoundEffect& out) {
        return sock
            << out.SoundId
            << out.SoundCategory
            << out.PosX << out.PosY << out.PosZ
            << out.Volume
            << out.Pitch;
    }
};