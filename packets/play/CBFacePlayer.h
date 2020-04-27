#pragma once

#include "../types/SocketPrimitives.h"

struct CBFacePlayer {
    static const int Id = 0x35;

    SocketVarInt AimAt; // 0: feet, 1: eyes
    SocketDouble AtX;
    SocketDouble AtY;
    SocketDouble AtZ;
    std::optional<SocketVarInt> EntityId;
    std::optional<SocketVarInt> EntityAt;


    friend SocketOStream& operator<<(SocketOStream& sock, const CBFacePlayer& out) {
        sock
            << out.AimAt
            << out.AtX << out.AtY << out.AtZ
            << SocketBool(out.EntityId.has_value());
        if (out.EntityId.has_value()) {
            sock
                << out.EntityId.value()
                << out.EntityAt.value();
        }
        return sock;
    }
};