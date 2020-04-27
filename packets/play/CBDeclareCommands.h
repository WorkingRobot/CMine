#pragma once

#include "../types/SocketPrimitives.h"

struct CBDeclareCommands {
    const int Id = 0x12;

    std::vector<SocketNode> Nodes;
    SocketVarInt RootInd;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBDeclareCommands& out) {
        sock << SocketVarInt(out.Nodes.size());
        for (auto& node : out.Nodes) {
            sock << node;
        }
        return sock << out.RootInd;
    }
};