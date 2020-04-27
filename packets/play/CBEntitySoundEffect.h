#pragma once

#include "../types/SocketPrimitives.h"

struct CBEntitySoundEffect {
    static const int Id = 0x51;

    SocketVarInt SoundId;
    SocketVarInt SoundCategory;
    SocketVarInt EntityId;
    SocketFloat Volume;
    SocketFloat Pitch;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBEntitySoundEffect& out) {
        return sock
            << out.SoundId
            << out.SoundCategory
            << out.EntityId
            << out.Volume
            << out.Pitch;
    }
};