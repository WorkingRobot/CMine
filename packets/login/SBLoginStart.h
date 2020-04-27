#pragma once

#include "../types/SocketPrimitives.h"

struct SBLoginStart {
    SocketString Name;

    friend SocketIStream& operator>>(SocketIStream& sock, SBLoginStart& out) {
        sock >> out.Name;
        return sock;
    }
};