#pragma once

#include "../types/SocketPrimitives.h"

struct CBCraftRecipeResp {
    static const int Id = 0x31;

    SocketUByte WindowId;
    SocketIdentifier RecipeId;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBCraftRecipeResp& out) {
        return sock
            << out.WindowId
            << out.RecipeId;
    }
};