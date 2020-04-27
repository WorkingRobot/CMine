#pragma once

#include "../types/SocketPrimitives.h"

struct SBLoginResp {
    SocketVarInt MessageID;
    SocketBool Successful;
    uint32_t DataLength;
    std::unique_ptr<char[]> Data;

    friend SocketIStream& operator>>(SocketIStream& sock, SBLoginResp& out) {
        sock >> out.MessageID;
        sock >> out.Successful;
        out.DataLength = sock.GetAvailableBufferSize();
        if (out.DataLength) {
            out.Data = std::make_unique<char[]>(out.DataLength);
            sock.Read(out.Data.get(), out.DataLength);
        }
        return sock;
    }
};