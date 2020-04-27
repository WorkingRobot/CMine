#pragma once

#include "../types/SocketPrimitives.h"

struct SBClientSettings {
    static const int Id = 0x05;

    SocketString Locale;
    SocketByte ViewDistance;
    SocketVarInt ChatMode; // 0: enabled, 1: commands/system, 2: hidden
    SocketBool ColorEnabled;
    SocketUByte SkinParts; // 0x01: cape, 0x02: jacket, 0x04: left sleeve, 0x08: right sleeve, 0x10: left pant, 0x20: right pant, 0x40: hat
    SocketVarInt MainHand; // 0: left, 1: right

    friend SocketIStream& operator>>(SocketIStream& sock, SBClientSettings& out) {
        return sock
            >> out.Locale
            >> out.ViewDistance
            >> out.ChatMode
            >> out.ColorEnabled
            >> out.SkinParts
            >> out.MainHand;
    }
};