#pragma once

#include "../types/SocketPrimitives.h"

struct SBEntityInteract {
    static const int Id = 0x0E;

    SocketVarInt EntityId;
    SocketVarInt Type; // 0: interact, 1: attack, 2: interact at
    std::optional<SocketFloat> TargetX;
    std::optional<SocketFloat> TargetY;
    std::optional<SocketFloat> TargetZ;
    std::optional<SocketVarInt> Hand; // 0: main hand, 1: off hand

    friend SocketIStream& operator>>(SocketIStream& sock, SBEntityInteract& out) {
        sock
            >> out.EntityId
            >> out.Type;
        if (out.Type == 2) {
            sock
                >> out.TargetX.emplace() >> out.TargetY.emplace() >> out.TargetZ.emplace();
        }
        if (out.Type == 0 || out.Type == 2) {
            sock
                >> out.Hand.emplace();
        }
        return sock;
    }
};