#pragma once

#include "../types/SocketPrimitives.h"

struct CBParticle {
    static const int Id = 0x24;

    SocketInt ParticleId;
    SocketBool LongDistance; // distance goes from 256 to 65536
    SocketDouble PosX;
    SocketDouble PosY;
    SocketDouble PosZ;
    SocketFloat OffX;
    SocketFloat OffY; // randomizer offset
    SocketFloat OffZ;
    SocketFloat ParticleData;
    SocketInt ParticleCount;
    SocketVaries Data;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBParticle& out) {
        return sock
            << out.ParticleId
            << out.LongDistance
            << out.PosX << out.PosY << out.PosZ
            << out.OffX << out.OffY << out.OffZ
            << out.ParticleData
            << out.ParticleCount
            << out.Data;
    }
};