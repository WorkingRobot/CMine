#pragma once

#include "../types/SocketPrimitives.h"

struct SBEncrResp {
    SocketVarInt SharedSecretLen; // Length of Shared Secret
    std::unique_ptr<char[]> SharedSecret;
    SocketVarInt VerifyTokenLen; // Length of Verify Token
    std::unique_ptr<char[]> VerifyToken;

    friend SocketIStream& operator>>(SocketIStream& sock, SBEncrResp& out) {
        sock >> out.SharedSecretLen;
        out.SharedSecret = std::make_unique<char[]>(out.SharedSecretLen.Value);
        sock.Read(out.SharedSecret.get(), out.SharedSecretLen.Value);
        sock >> out.VerifyTokenLen;
        out.VerifyToken = std::make_unique<char[]>(out.VerifyTokenLen.Value);
        sock.Read(out.VerifyToken.get(), out.VerifyTokenLen.Value);
        return sock;
    }
};