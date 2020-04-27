#pragma once

#include "../types/SocketPrimitives.h"

struct CBOpenSignEditor {
    const int Id = 0x30;

    SocketPosition Location;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBOpenSignEditor& out) {
        return sock
            << out.Location;
    }
};