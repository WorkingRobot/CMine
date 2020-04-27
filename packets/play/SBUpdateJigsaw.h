#pragma once

#include "../types/SocketPrimitives.h"

struct SBUpdateJigsaw {
    static const int Id = 0x27;

    SocketPosition Location;
    SocketIdentifier AttatchmentType;
    SocketIdentifier TargetPool;
    SocketString FinalState;

    friend SocketIStream& operator>>(SocketIStream& sock, SBUpdateJigsaw& out) {
        return sock
            >> out.Location
            >> out.AttatchmentType
            >> out.TargetPool
            >> out.FinalState;
    }
};