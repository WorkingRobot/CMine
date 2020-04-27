#pragma once

#include "../types/SocketPrimitives.h"

struct CBUpdateLight {
    static const int Id = 0x25;

    SocketVarInt ChunkX;
    SocketVarInt ChunkZ;
    SocketVarInt SkyLightMask;
    SocketVarInt BlockLightMask;
    SocketVarInt EmptySkyLightMask;
    SocketVarInt EmptyBlockLightMask;
    std::vector<SocketUByte> SkyLights;
    std::vector<SocketUByte> BlockLights;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBUpdateLight& out) {
        sock
            << out.ChunkX << out.ChunkZ
            << out.SkyLightMask
            << out.BlockLightMask
            << out.EmptySkyLightMask
            << out.EmptyBlockLightMask;
        sock << SocketVarInt(out.SkyLights.size()); // always 2048
        for (auto& b : out.SkyLights) {
            sock << b;
        }
        sock << SocketVarInt(out.BlockLights.size()); // always 2048
        for (auto& b : out.BlockLights) {
            sock << b;
        }
        return sock;
    }
};