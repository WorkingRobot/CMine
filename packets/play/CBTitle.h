#pragma once

#include "../types/SocketPrimitives.h"

struct CBTitle {
    static const int Id = 0x50;

    SocketVarInt Action;

    // 0: set title
    // 1: set subtitle
    // 2: set actionbar
    SocketChat Text;

    // 3: set times
    SocketInt FadeIn;
    SocketInt StayTime;
    SocketInt FadeOut;

    // 4: hide
    // no fields

    // 5: reset
    // no fields

    friend SocketOStream& operator<<(SocketOStream& sock, const CBTitle& out) {
        sock << out.Action;
        switch (out.Action)
        {
        case 0:
        case 1:
        case 2:
            sock << out.Text;
            break;
        case 3:
            sock
                << out.FadeIn
                << out.StayTime
                << out.FadeOut;
            break;
        case 4:
        case 5:
            break;
        }
        return sock;
    }
};