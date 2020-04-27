#pragma once

#include "../types/SocketPrimitives.h"

struct CBPlayerListHeaderFooter {
    const int Id = 0x54;

    SocketChat Header; // to remove: {"translate":""}
    SocketChat Footer;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBPlayerListHeaderFooter& out) {
        return sock
            << out.Header
            << out.Footer;
    }
};