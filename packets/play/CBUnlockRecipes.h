#pragma once

#include "../types/SocketPrimitives.h"

struct CBUnlockRecipes {
    static const int Id = 0x37;

    SocketVarInt Action;
    SocketBool CraftingOpen;
    SocketBool CraftingFilterActive;
    SocketBool SmeltingOpen;
    SocketBool SmeltingFilterActive;
    std::vector<SocketIdentifier> Recipes1;
    std::optional<std::vector<SocketIdentifier>> Recipes2;


    friend SocketOStream& operator<<(SocketOStream& sock, const CBUnlockRecipes& out) {
        sock
            << out.Action
            << out.CraftingOpen << out.CraftingFilterActive
            << out.SmeltingOpen << out.SmeltingFilterActive
            << SocketVarInt(out.Recipes1.size());
        for (auto& recipe : out.Recipes1) {
            sock << recipe;
        }
        if (out.Action == 0) {
            sock << SocketVarInt(out.Recipes2.value().size());
            for (auto& recipe : out.Recipes2.value()) {
                sock << recipe;
            }
        }
        return sock;
    }
};