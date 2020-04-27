#pragma once

#include "../types/SocketPrimitives.h"

struct CBAdvancements {
    static const int Id = 0x58;

    struct Display {
        SocketChat Title;
        SocketChat Description;
        SocketSlot Icon;
        SocketVarInt FrameType;
        SocketInt Flags;
        std::optional<SocketIdentifier> Background;
        SocketFloat PosX;
        SocketFloat PosY;
    };

    struct Criterion {
        SocketIdentifier Key;
        // void value
    };

    struct CriterionProgress {
        SocketIdentifier Id;
        std::optional<SocketLong> AchievementTime;
    };

    struct Advancement {
        std::optional<SocketIdentifier> Parent;
        std::optional<Display> Display;
        std::vector<Criterion> Criteria;
        std::vector<std::vector<SocketString>> Requirements;
    };

    struct Mapping {
        SocketIdentifier Key;
        Advancement Value;
    };

    struct ProgMapping {
        SocketIdentifier Key;
        std::vector<CriterionProgress> Value;
    };
    
    SocketBool Reset;
    std::vector<Mapping> Mappings;
    std::vector<SocketIdentifier> Removed;
    std::vector<ProgMapping> Progress;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBAdvancements& out) {
        sock
            << out.Reset
            << SocketVarInt(out.Mappings.size());
        for (auto& mapping : out.Mappings) {
            sock << mapping.Key;

            sock << SocketBool(mapping.Value.Parent.has_value());
            if (mapping.Value.Parent.has_value()) {
                sock << mapping.Value.Parent.value();
            }
            sock << SocketBool(mapping.Value.Display.has_value());
            if (mapping.Value.Display.has_value()) {
                auto& disp = mapping.Value.Display.value();
                sock
                    << disp.Title
                    << disp.Description
                    << disp.Icon
                    << disp.FrameType
                    << disp.Flags
                    << SocketBool(disp.Flags & 0x1);
                if (disp.Flags & 0x1) {
                    sock << disp.Background.value();
                }
                sock << disp.PosX << disp.PosY;
            }
            sock << SocketVarInt(mapping.Value.Criteria.size());
            for (auto& criterion : mapping.Value.Criteria) {
                sock << criterion.Key;
            }
            sock << SocketVarInt(mapping.Value.Requirements.size());
            for (auto& requirement : mapping.Value.Requirements) {
                sock << SocketVarInt(requirement.size());
                for (auto& req : requirement) {
                    sock << req;
                }
            }
        }
        sock << SocketVarInt(out.Removed.size());
        for (auto& adv : out.Removed) {
            sock << adv;
        }
        sock << SocketVarInt(out.Progress.size());
        for (auto& prog : out.Progress) {
            sock << prog.Key;

            sock << SocketVarInt(prog.Value.size());
            for (auto& advProg : prog.Value) {
                sock
                    << advProg.Id
                    << SocketBool(advProg.AchievementTime.has_value());
                if (advProg.AchievementTime.has_value()) {
                    sock << advProg.AchievementTime.value();
                }
            }
        }
    }
};