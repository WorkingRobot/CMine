#pragma once

#include "../types/SocketPrimitives.h"

struct CBDeclareRecipes {
    static const int Id = 0x5B;

    struct Recipe {
        SocketIdentifier Id;
        SocketString Type;
        SocketVaries Data;
    };

    std::vector<Recipe> Recipes;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBDeclareRecipes& out) {
        sock << SocketVarInt(out.Recipes.size());
        for (auto& recipe : out.Recipes) {
            sock
                << recipe.Id
                << recipe.Type
                << recipe.Data;
        }
        return sock;
    }
};