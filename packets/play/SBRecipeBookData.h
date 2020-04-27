#pragma once

#include "../types/SocketPrimitives.h"

struct SBRecipeBookData {
    static const int Id = 0x1D;

    SocketVarInt Type;

    // 0: displayed recipe
    SocketIdentifier RecipeId;

    // 1: book states
    SocketBool CraftingOpen;
    SocketBool CraftingFilterActive;
    SocketBool SmeltingOpen;
    SocketBool SmeltingFilterActive;
    SocketBool BlastingOpen;
    SocketBool BlastingFilterActive;
    SocketBool SmokingOpen;
    SocketBool SmokingFilterActive;

    friend SocketIStream& operator>>(SocketIStream& sock, SBRecipeBookData& out) {
        sock >> out.Type;
        switch (out.Type)
        {
        case 0:
            sock >> out.RecipeId;
            break;
        case 1:
            sock
                >> out.CraftingOpen
                >> out.CraftingFilterActive
                >> out.SmeltingOpen
                >> out.SmeltingFilterActive
                >> out.BlastingOpen
                >> out.BlastingFilterActive
                >> out.SmokingOpen
                >> out.SmokingFilterActive;
        }
        return sock;
    }
};