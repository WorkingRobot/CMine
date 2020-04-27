#pragma once

#include "../types/SocketPrimitives.h"

struct CBSelectAdvancementTab {
    static const int Id = 0x3D;

    std::optional<SocketIdentifier> Identifier;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBSelectAdvancementTab& out) {
        sock << SocketBool(out.Identifier.has_value());
        if (out.Identifier.has_value()) {
            sock << out.Identifier.value();
        }
        return sock;
    }
};