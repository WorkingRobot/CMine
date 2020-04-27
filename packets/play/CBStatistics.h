#pragma once

#include "../types/SocketPrimitives.h"

#include <vector>

struct CBStatistics {
    static const int Id = 0x07;

    struct Statistic {
        SocketVarInt CategoryId;
        SocketVarInt StatisticId;
    };

    std::vector<Statistic> Statistics;
    SocketVarInt Value;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBStatistics& out) {
        sock << SocketVarInt(out.Statistics.size());
        for (auto& stat : out.Statistics) {
            sock << stat.CategoryId << stat.StatisticId;
        }
        return sock << out.Value;
    }
};