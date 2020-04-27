#pragma once

#include "../types/SocketPrimitives.h"

#include <vector>
#include <optional>

struct CBMapData {
    const int Id = 0x27;

    struct Icon {
        SocketVarInt Type;
        SocketByte X;
        SocketByte Z;
        SocketByte Direction;
        std::optional<SocketChat> DisplayName;
    };

    SocketVarInt MapId;
    SocketByte Scale;
    SocketBool TrackingPosition;
    SocketBool Locked;
    std::vector<Icon> Icons;
    SocketUByte Columns;
    std::optional<SocketByte> Rows;
    std::optional<SocketByte> X;
    std::optional<SocketByte> Z;
    std::optional<std::vector<SocketUByte>> Data;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBMapData& out) {
        sock
            << out.MapId
            << out.Scale
            << out.TrackingPosition
            << out.Locked
            << SocketVarInt(out.Icons.size());
        for (auto& icon : out.Icons) {
            sock
                << icon.Type
                << icon.X << icon.Z
                << icon.Direction
                << SocketBool(icon.DisplayName.has_value());
            if (icon.DisplayName.has_value()) {
                sock << icon.DisplayName.value();
            }
        }
        sock << out.Columns;
        if (out.Columns > 0) {
            sock
                << out.Rows.value()
                << out.X.value()
                << out.Z.value()
                << SocketVarInt(out.Data.has_value());
            for (auto& b : out.Data.value()) {
                sock << b;
            }
        }
        return sock;
    }
};