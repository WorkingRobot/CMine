#pragma once

#include "../types/SocketPrimitives.h"

struct SBUpdateCmdMinecart {
    static const int Id = 0x25;

    SocketVarInt EntityId;
    SocketString Command;
    SocketBool TrackOutput;

    friend SocketIStream& operator>>(SocketIStream& sock, SBUpdateCmdMinecart& out) {
        return sock
            >> out.EntityId
            >> out.Command
            >> out.TrackOutput;
    }
};