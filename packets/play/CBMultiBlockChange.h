#pragma once

#include "../types/SocketPrimitives.h"

#include <vector>

struct CBMultiBlockChange {
    const int Id = 0x10;

    struct Record {
        SocketUByte HPos; // 0xF0 -> X, 0x0F -> Z
        SocketUByte YPos;
        SocketVarInt BlockId;
    };

    SocketInt ChunkX;
    SocketInt ChunkZ;
    std::vector<Record> Records;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBMultiBlockChange& out) {
        sock << out.ChunkX << out.ChunkZ
            << SocketVarInt(out.Records.size());
        for (auto& record : out.Records) {
            sock << record.HPos << record.YPos << record.BlockId;
        }
        return sock;
    }
};