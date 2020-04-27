#pragma once

#include "../types/SocketPrimitives.h"

struct CBEntityProperties {
    static const int Id = 0x59;

    struct Modifier {
        SocketGUID Uuid;
        SocketDouble Amount;
        SocketByte Operation; // 0: add/subtract, 1: add/subtract percent, 2: multiply percent
    };

    struct Property {
        SocketString Key;
        SocketDouble Value;
        std::vector<Modifier> Modifiers;
    };

    SocketVarInt EntityId;
    std::vector<Property> Properties;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBEntityProperties& out) {
        sock
            << out.EntityId
            << SocketVarInt(out.Properties.size());
        for (auto& prop : out.Properties) {
            sock
                << prop.Key
                << prop.Value
                << SocketVarInt(prop.Modifiers.size());
            for (auto& mod : prop.Modifiers) {
                sock
                    << mod.Uuid
                    << mod.Amount
                    << mod.Operation;
            }
        }
    }
};