#pragma once

#include "../types/SocketPrimitives.h"

struct SBAdvancementTab {
    static const int Id = 0x20;

    SocketVarInt Action; // 0: opened, 1: closed
    std::optional<SocketIdentifier> TabId;

    friend SocketIStream& operator>>(SocketIStream& sock, SBAdvancementTab& out) {
        sock >> out.Action;
        if (out.Action == 0) {
            sock >> out.TabId.emplace();
        }
        return sock;
    }
};