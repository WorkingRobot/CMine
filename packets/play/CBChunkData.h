#pragma once

#include "../types/SocketPrimitives.h"

struct CBChunkData {
    const int Id = 0x22;

    SocketInt ChunkX;
    SocketInt ChunkZ;
    SocketBool FullChunk;
    SocketVarInt Bitmask;
    SocketNBT Heightmaps;
    std::optional<std::vector<SocketInt>> Biomes;
    SocketString Data; // byte array with varint before it
    std::vector<SocketNBT> BlockEntities;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBChunkData& out) {
        sock
            << out.ChunkX << out.ChunkZ
            << out.FullChunk
            << out.Bitmask
            << out.Heightmaps;
        if (out.FullChunk) {
            sock << SocketVarInt(out.Biomes.value().size()); // unsure if this is added, wiki.vg states it's always 1024
            for (auto& biome : out.Biomes.value()) {
                sock << biome;
            }
        }
        sock << out.Data;
        sock << SocketVarInt(out.BlockEntities.size());
        for (auto& block : out.BlockEntities) {
            sock << block;
        }
    }
};