#pragma once

#include "../types/SocketPrimitives.h"

#include <optional>
#include <vector>

struct CBTabComplete {
    const int Id = 0x11;

    struct Match {
        SocketString Match;
        std::optional<SocketChat> Tooltip;
    };

    SocketVarInt TransactionId;
    SocketVarInt Start;
    SocketVarInt Length;
    std::vector<Match> Matches;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBTabComplete& out) {
        sock << out.TransactionId << out.Start << out.Length << SocketVarInt(out.Matches.size());
        for (auto& match : out.Matches) {
            sock << match.Match << SocketBool(match.Tooltip.has_value());
            if (match.Tooltip.has_value()) {
                sock << match.Tooltip.value();
            }
        }
    }
};