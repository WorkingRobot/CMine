#pragma once

#include "../types/SocketPrimitives.h"

struct SBRequest { // no fields
    friend SocketIStream& operator>>(SocketIStream& sock, SBRequest& out) {
        return sock;
    }
};