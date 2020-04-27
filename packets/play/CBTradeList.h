#pragma once

#include "../types/SocketPrimitives.h"

#include <vector>
#include <optional>

struct CBTradeList {
    static const int Id = 0x28;

    struct Trade {
        SocketSlot Input1;
        SocketSlot Output;
        std::optional<SocketSlot> Input2;
        SocketBool Disabled;
        SocketInt TradeUses;
        SocketInt MaxTradeUses;
        SocketInt XP;
        SocketInt SpecialPrice;
        SocketFloat PriceMultiplier;
        SocketInt Demand;
    };

    SocketVarInt WindowId;
    std::vector<Trade> Trades;
    SocketVarInt VillagerLevel; // 1-5
    SocketVarInt Experience; // total
    SocketBool RegularVillager; // if false, some gui is hidden (wandering villager)
    SocketBool Restockable;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBTradeList& out) {
        sock
            << out.WindowId
            << SocketUByte(out.Trades.size());
        for (auto& trade : out.Trades) {
            sock
                << trade.Input1
                << trade.Output
                << SocketBool(trade.Input2.has_value());
            if (trade.Input2.has_value()) {
                sock << trade.Input2.value();
            }
            sock
                << trade.Disabled
                << trade.TradeUses
                << trade.MaxTradeUses
                << trade.XP
                << trade.SpecialPrice
                << trade.PriceMultiplier
                << trade.Demand;
        }
        return sock
            << out.VillagerLevel
            << out.Experience
            << out.RegularVillager
            << out.Restockable;
    }
};