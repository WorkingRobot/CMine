#pragma once

#include "../types/SocketPrimitives.h"

struct CBEntityEffect {
    static const int Id = 0x5A;

    SocketVarInt EntityId;
    SocketByte EffectId;
    SocketByte Amplifier;
    SocketVarInt Duration;
    SocketByte Flags; // 0x1: ambient, 0x2: show particles, 0x4: show icon

    friend SocketOStream& operator<<(SocketOStream& sock, const CBEntityEffect& out) {
        return sock
            << out.EntityId
            << out.EffectId
            << out.Amplifier
            << out.Duration
            << out.Flags;
    }
};