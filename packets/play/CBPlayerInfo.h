#pragma once

#include "../types/SocketPrimitives.h"

struct CBPlayerInfo {
    const int Id = 0x34;

    struct Property {
        SocketString Name;
        SocketString Value;
        std::optional<SocketString> Signature;
    };

    struct Player {
        SocketGUID Uuid;

        // 0: add player
        SocketString Name;
        std::vector<Property> Properties;
        SocketVarInt Gamemode;
        SocketVarInt Ping;
        std::optional<SocketChat> DisplayName;

        // 1: update gamemode
        // Gamemode

        // 2: update latency
        // Ping

        // 3: update display name
        // DisplayName

        // 4: remove player
        // no fields
    };

    SocketVarInt Action; // enum
    std::vector<Player> Players;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBPlayerInfo& out) {
        sock << out.Action << SocketVarInt(out.Players.size());
        for (auto& player : out.Players) {
            sock << player.Uuid;
            switch (out.Action)
            {
            case 0:
                sock
                    << player.Name
                    << SocketVarInt(player.Properties.size());
                for (auto& prop : player.Properties) {
                    sock
                        << prop.Name
                        << prop.Value
                        << SocketBool(prop.Signature.has_value());
                    if (prop.Signature.has_value()) {
                        sock << prop.Signature.value();
                    }
                }
                sock
                    << player.Gamemode
                    << player.Ping
                    << SocketBool(player.DisplayName.has_value());
                if (player.DisplayName.has_value()) {
                    sock << player.DisplayName.value();
                }
                break;
            case 1:
                sock << player.Gamemode;
                break;
            case 2:
                sock << player.Ping;
                break;
            case 3:
                sock << SocketBool(player.DisplayName.has_value());
                if (player.DisplayName.has_value()) {
                    sock << player.DisplayName.value();
                }
                break;
            case 4:
                break;
            }
        }
    }
};