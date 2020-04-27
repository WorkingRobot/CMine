#pragma once

#include "../types/SocketPrimitives.h"

struct CBExplosion {
    static const int Id = 0x1D;

    struct Record {
        SocketByte X;
        SocketByte Y; // positions are relative from center
        SocketByte Z;
    };

    SocketFloat PosX;
    SocketFloat PosY;
    SocketFloat PosZ;
    SocketFloat Strength; // >= 2 -> minecraft:explosion_emitter particle, < 2 -> minecraft:explosion
    std::vector<Record> Records; // affected blocks
    SocketFloat PlayerMotionX;
    SocketFloat PlayerMotionY;
    SocketFloat PlayerMotionZ;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBExplosion& out) {
        sock << out.PosX << out.PosY << out.PosZ << out.Strength << SocketVarInt(out.Records.size());
        for (auto& record : out.Records) {
            sock << record.X << record.Y << record.Z;
        }
        return sock
            << out.PlayerMotionX << out.PlayerMotionY << out.PlayerMotionZ;
    }
};