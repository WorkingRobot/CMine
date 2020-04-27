#pragma once

#include "../types/SocketPrimitives.h"

struct CBTeams {
    static const int Id = 0x4C;

    SocketString Name; // 16 chars
    SocketByte Mode;

    // 0: create team
    SocketChat DisplayName;
    SocketByte FriendlyFlags; // 0x01: allow friendly fire. 0x02: can see invisible players on same team
    SocketString NameTagVisibility; // always, hideForOtherTeams, hideForOwnTeam, or never
    SocketString CollisionRule; // always, pushOtherTeams, pushOwnTeam, or never
    SocketVarInt Color;
    SocketChat Prefix;
    SocketChat Suffix;
    std::vector<SocketString> Entities; // username (players) or uuid (entity)

    // 1: remove team
    // no fields
    
    // 2: update team info
    // DisplayName
    // FriendlyFlags
    // NameTagVisibility
    // CollisionRule
    // Color
    // Prefix
    // Suffix

    // 3: add players
    // Entities (entities added)

    // 4: remove players
    // Entities (entities removed)

    friend SocketOStream& operator<<(SocketOStream& sock, const CBTeams& out) {
        sock
            << out.Name
            << out.Mode;
        switch (out.Mode)
        {
        case 0:
            sock
                << out.DisplayName
                << out.FriendlyFlags
                << out.NameTagVisibility
                << out.CollisionRule
                << out.Color
                << out.Prefix
                << out.Suffix
                << SocketVarInt(out.Entities.size());
            for (auto& entity : out.Entities) {
                sock << entity;
            }
            break;
        case 1:
            break;
        case 2:
            sock
                << out.DisplayName
                << out.FriendlyFlags
                << out.NameTagVisibility
                << out.CollisionRule
                << out.Color
                << out.Prefix
                << out.Suffix;
            break;
        case 3:
        case 4:
            sock << SocketVarInt(out.Entities.size());
            for (auto& entity : out.Entities) {
                sock << entity;
            }
            break;
        }
        return sock;
    }
};