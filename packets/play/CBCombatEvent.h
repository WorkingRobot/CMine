#pragma once

#include "../types/SocketPrimitives.h"

struct CBCombatEvent {
    static const int Id = 0x33;

    SocketVarInt Event; // enum

    // 0: enter combat
    // nothing

    // 1: end combat
    SocketVarInt Duration;
    SocketInt EntityId;

    // 2: entity dead
    SocketVarInt PlayerId;
    // EntityId
    SocketChat DeathMessage;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBCombatEvent& out) {
        sock << out.Event;
        switch (out.Event)
        {
        case 0x00:
            break;
        case 0x01:
            sock << out.Duration << out.EntityId;
            break;
        case 0x02:
            sock << out.PlayerId << out.EntityId << out.DeathMessage;
            break;
        }
        return sock;
    }
};