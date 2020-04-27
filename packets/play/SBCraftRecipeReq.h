#pragma once

#include "../types/SocketPrimitives.h"

struct SBCraftRecipeReq {
    static const int Id = 0x18;

    SocketByte WindowId;
    SocketIdentifier RecipeId;
    SocketBool MakeAll;

    friend SocketIStream& operator>>(SocketIStream& sock, SBCraftRecipeReq& out) {
        return sock
            >> out.WindowId
            >> out.RecipeId
            >> out.MakeAll;
    }
};