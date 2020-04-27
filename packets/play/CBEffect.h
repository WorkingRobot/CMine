#pragma once

#include "../types/SocketPrimitives.h"

struct CBEffect {
    static const int Id = 0x23;

    SocketInt EffectId;
    SocketPosition Location;
    SocketInt Data;
    SocketBool DisableRelativeVolume; // basically LODs, only used in 2 effects

    friend SocketOStream& operator<<(SocketOStream& sock, const CBEffect& out) {
        return sock
            << out.EffectId
            << out.Location
            << out.Data
            << out.DisableRelativeVolume;
    }
};