#pragma once

#include "../types/SocketPrimitives.h"

struct CBTags {
    const int Id = 0x5C;

    struct Tag {
        SocketIdentifier Name;
        std::vector<SocketVarInt> Entries;
    };

    std::vector<Tag> Blocks;
    std::vector<Tag> Items;
    std::vector<Tag> Fluids;
    std::vector<Tag> Entities;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBTags& out) {
        sock << SocketVarInt(out.Blocks.size());
        for (auto& tag : out.Blocks) {
            sock
                << tag.Name
                << SocketVarInt(tag.Entries.size());
            for (auto& entry : tag.Entries) {
                sock << entry;
            }
        }

        sock << SocketVarInt(out.Items.size());
        for (auto& tag : out.Items) {
            sock
                << tag.Name
                << SocketVarInt(tag.Entries.size());
            for (auto& entry : tag.Entries) {
                sock << entry;
            }
        }

        sock << SocketVarInt(out.Fluids.size());
        for (auto& tag : out.Fluids) {
            sock
                << tag.Name
                << SocketVarInt(tag.Entries.size());
            for (auto& entry : tag.Entries) {
                sock << entry;
            }
        }

        sock << SocketVarInt(out.Entities.size());
        for (auto& tag : out.Entities) {
            sock
                << tag.Name
                << SocketVarInt(tag.Entries.size());
            for (auto& entry : tag.Entries) {
                sock << entry;
            }
        }
        return sock;
    }
};