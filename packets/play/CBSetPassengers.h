#pragma once

#include "../types/SocketPrimitives.h"

struct CBSetPassengers {
    const int Id = 0x4B;

    SocketVarInt VehicleId;
    std::vector<SocketVarInt> Passengers;

    friend SocketOStream& operator<<(SocketOStream& sock, const CBSetPassengers& out) {
        sock
            << out.VehicleId
            << SocketVarInt(out.Passengers.size());
        for (auto& passenger : out.Passengers) {
            sock << passenger;
        }
        return sock;
    }
};