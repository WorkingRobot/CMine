#pragma once

#include "SocketIStream.h"
#include "SocketOStream.h"

#include <WinSock2.h>

#include <optional>
#include <memory>
#include <string>
#include <vector>

class SocketVarInt {
public:
    int32_t Value;

    SocketVarInt() : Value(0) { }
    SocketVarInt(int32_t val) : Value(val) { }
    operator int32_t& () { return Value; }
    operator int32_t() const { return Value; }

    uint8_t GetSize() const {
        uint8_t size = 0;
        uint32_t value = Value;
        do {
            uint8_t temp = value & 0b01111111;
            value >>= 7;
            if (value != 0) {
                temp |= 0b10000000;
            }
            size++;
        } while (value != 0);
        return size;
    }

    friend SocketOStream& operator<<(SocketOStream& sock, const SocketVarInt& out) {
        uint32_t value = out.Value;
        do {
            uint8_t temp = value & 0b01111111;
            value >>= 7;
            if (value != 0) {
                temp |= 0b10000000;
            }
            sock.WriteByte(temp);
        } while (value != 0);
        return sock;
    }

    friend SocketIStream& operator>>(SocketIStream& sock, SocketVarInt& out) {
        uint8_t numRead = 0;
        int32_t result = 0;
        uint8_t read;
        do {
            read = sock.ReadByte();
            result |= ((read & 0b01111111) << (7 * numRead));

            numRead++;
            if (numRead > 5) {
                out.Value = -1;
                return sock;
            }
        } while ((read & 0b10000000) != 0);

        out.Value = result;
        return sock;
    }
};

class SocketVarLong {
public:
    int64_t Value;

    SocketVarLong() : Value(0) { }
    SocketVarLong(int64_t val) : Value(val) { }
    operator int64_t& () { return Value; }
    operator int64_t() const { return Value; }

    uint8_t GetSize() {
        uint8_t size;
        uint32_t value = Value;
        do {
            uint8_t temp = value & 0b01111111;
            value >>= 7;
            if (value != 0) {
                temp |= 0b10000000;
            }
            size++;
        } while (value != 0);
        return size;
    }

    friend SocketOStream& operator<<(SocketOStream& sock, const SocketVarLong& out) {
        uint64_t value = out.Value;
        do {
            uint8_t temp = value & 0b01111111;
            value >>= 7;
            if (value != 0) {
                temp |= 0b10000000;
            }
            sock.WriteByte(temp);
        } while (value != 0);
        return sock;
    }

    friend SocketIStream& operator>>(SocketIStream& sock, SocketVarLong& out) {
        uint8_t numRead = 0;
        int64_t result = 0;
        uint8_t read;
        do {
            read = sock.ReadByte();
            result |= ((read & 0b01111111) << (7 * numRead));

            numRead++;
            if (numRead > 10) {
                out.Value = -1;
                return sock;
            }
        } while ((read & 0b10000000) != 0);

        out.Value = result;
        return sock;
    }
};

class SocketString {
public:
    SocketVarInt Length;
    std::unique_ptr<char[]> Data;

    SocketString() : Length(0) { }
    SocketString(std::string& val) { SetValue(val); }
    operator std::string& () { return std::string(Data.get(), Data.get() + Length); }
    operator std::string() const { return std::string(Data.get(), Data.get() + Length); }

    SocketString(const char* val, int valSize) { SetValue(val, valSize); }
    operator char* () { return Data.get(); }
    operator char* () const { return Data.get(); }

    SocketString(const char* data) {
        Length = strlen(data);
        Data = std::make_unique<char[]>(Length + 1);
        memcpy(Data.get(), data, Length.Value + 1);
    }

    void SetValue(const std::string& str) {
        Length = str.size();
        Data.reset(new char[Length + 1]);
        memcpy(Data.get(), str.data(), Length);
        Data[Length] = '\0';
    }

    void SetValue(const char* str, int strSize) {
        Length = strSize;
        Data.reset(new char[strSize]);
        memcpy(Data.get(), str, strSize);
    }

    friend SocketOStream& operator<<(SocketOStream& sock, const SocketString& out) {
        sock << out.Length;
        sock.Write(out.Data.get(), out.Length);
        return sock;
    }

    friend SocketIStream& operator>>(SocketIStream& sock, SocketString& out) {
        sock >> out.Length;
        out.Data = std::make_unique<char[]>(out.Length + 1);
        sock.Read(out.Data.get(), out.Length);
        out.Data[out.Length] = '\0';
        return sock;
    }
};

typedef SocketString SocketChat; // for now?
typedef SocketString SocketIdentifier; // for now?

class SocketBool {
public:
    bool Value;

    SocketBool() : Value(false) { }
    SocketBool(bool val) : Value(val) { }
    operator bool& () { return Value; }
    operator bool() const { return Value; }

    friend SocketOStream& operator<<(SocketOStream& sock, const SocketBool& out) {
        sock.Write((const char*)&out.Value, sizeof(bool));
        return sock;
    }

    friend SocketIStream& operator>>(SocketIStream& sock, SocketBool& out) {
        sock.Read((char*)&out.Value, sizeof(bool));
        return sock;
    }
};

class SocketByte {
public:
    int8_t Value;

    SocketByte() : Value(0) { }
    SocketByte(int8_t val) : Value(val) { }
    operator int8_t& () { return Value; }
    operator int8_t() const { return Value; }

    friend SocketOStream& operator<<(SocketOStream& sock, const SocketByte& out) {
        sock.Write((const char*)&out.Value, sizeof(int8_t));
        return sock;
    }

    friend SocketIStream& operator>>(SocketIStream& sock, SocketByte& out) {
        sock.Read((char*)&out.Value, sizeof(int8_t));
        return sock;
    }
};

class SocketUByte {
public:
    uint8_t Value;

    SocketUByte() : Value(0) { }
    SocketUByte(uint8_t val) : Value(val) { }
    operator uint8_t& () { return Value; }
    operator uint8_t() const { return Value; }

    friend SocketOStream& operator<<(SocketOStream& sock, const SocketUByte& out) {
        sock.Write((const char*)&out.Value, sizeof(uint8_t));
        return sock;
    }

    friend SocketIStream& operator>>(SocketIStream& sock, SocketUByte& out) {
        sock.Read((char*)&out.Value, sizeof(uint8_t));
        return sock;
    }
};

class SocketShort {
public:
    int16_t Value;

    SocketShort() : Value(0) { }
    SocketShort(int16_t val) : Value(val) { }
    operator int16_t& () { return Value; }
    operator int16_t() const { return Value; }

    friend SocketOStream& operator<<(SocketOStream& sock, const SocketShort& out) {
        auto temp = htons(out.Value);
        sock.Write((const char*)&temp, sizeof(int16_t));
        return sock;
    }

    friend SocketIStream& operator>>(SocketIStream& sock, SocketShort& out) {
        sock.Read((char*)&out.Value, sizeof(int16_t));
        out.Value = ntohs(out.Value);
        return sock;
    }
};

class SocketUShort {
public:
    uint16_t Value;

    SocketUShort() : Value(0) { }
    SocketUShort(uint16_t val) : Value(val) { }
    operator uint16_t& () { return Value; }
    operator uint16_t() const { return Value; }

    friend SocketOStream& operator<<(SocketOStream& sock, const SocketUShort& out) {
        auto temp = htons(out.Value);
        sock.Write((const char*)&temp, sizeof(uint16_t));
        return sock;
    }

    friend SocketIStream& operator>>(SocketIStream& sock, SocketUShort& out) {
        sock.Read((char*)&out.Value, sizeof(uint16_t));
        out.Value = ntohs(out.Value);
        return sock;
    }
};

class SocketInt {
public:
    int32_t Value;

    SocketInt() : Value(0) { }
    SocketInt(int32_t val) : Value(val) { }
    operator int32_t& () { return Value; }
    operator int32_t() const { return Value; }

    friend SocketOStream& operator<<(SocketOStream& sock, const SocketInt& out) {
        auto temp = htonl(out.Value);
        sock.Write((const char*)&temp, sizeof(int32_t));
        return sock;
    }

    friend SocketIStream& operator>>(SocketIStream& sock, SocketInt& out) {
        sock.Read((char*)&out.Value, sizeof(int32_t));
        out.Value = htonl(out.Value);
        return sock;
    }
};

class SocketLong {
public:
    int64_t Value;

    SocketLong() : Value(0) { }
    SocketLong(int64_t val) : Value(val) { }
    operator int64_t& () { return Value; }
    operator int64_t() const { return Value; }

    friend SocketOStream& operator<<(SocketOStream& sock, const SocketLong& out) {
        auto temp = htonll(out.Value);
        sock.Write((const char*)&temp, sizeof(int64_t));
        return sock;
    }

    friend SocketIStream& operator>>(SocketIStream& sock, SocketLong& out) {
        sock.Read((char*)&out.Value, sizeof(int64_t));
        out.Value = htonll(out.Value);
        return sock;
    }
};

class SocketGUID {
public:
    uint32_t A;
    uint32_t B;
    uint32_t C;
    uint32_t D;

    SocketGUID() : A(0), B(0), C(0), D(0) { }
    SocketGUID(uint32_t a, uint32_t b, uint32_t c, uint32_t d) : A(a), B(b), C(c), D(d) { }

    friend SocketOStream& operator<<(SocketOStream& sock, const SocketGUID& out) {
        auto temp = htonl(out.A);
        sock.Write((const char*)&temp, sizeof(uint32_t));
        temp = htonl(out.B);
        sock.Write((const char*)&temp, sizeof(uint32_t));
        temp = htonl(out.C);
        sock.Write((const char*)&temp, sizeof(uint32_t));
        temp = htonl(out.D);
        sock.Write((const char*)&temp, sizeof(uint32_t));
        return sock;
    }

    friend SocketIStream& operator>>(SocketIStream& sock, SocketGUID& out) {
        sock.Read((char*)&out.A, sizeof(uint32_t));
        sock.Read((char*)&out.B, sizeof(uint32_t));
        sock.Read((char*)&out.C, sizeof(uint32_t));
        sock.Read((char*)&out.D, sizeof(uint32_t));
        out.A = htonl(out.A);
        out.B = htonl(out.B);
        out.C = htonl(out.C);
        out.D = htonl(out.D);
        return sock;
    }
};

class SocketDouble {
public:
    double Value;

    SocketDouble() : Value(0) { }
    SocketDouble(double val) : Value(val) { }
    operator double& () { return Value; }
    operator double() const { return Value; }

    friend SocketOStream& operator<<(SocketOStream& sock, const SocketDouble& out) {
        auto temp = htond(out.Value);
        sock.Write((const char*)&temp, sizeof(int64_t));
        return sock;
    }

    friend SocketIStream& operator>>(SocketIStream& sock, SocketDouble& out) {
        sock.Read((char*)&out.Value, sizeof(int64_t));
        out.Value = htond(out.Value);
        return sock;
    }
};

class SocketFloat {
public:
    float Value;

    SocketFloat() : Value(0) { }
    SocketFloat(float val) : Value(val) { }
    operator float& () { return Value; }
    operator float() const { return Value; }

    friend SocketOStream& operator<<(SocketOStream& sock, const SocketFloat& out) {
        auto temp = htonf(out.Value);
        sock.Write((const char*)&temp, sizeof(int32_t));
        return sock;
    }

    friend SocketIStream& operator>>(SocketIStream& sock, SocketFloat& out) {
        sock.Read((char*)&out.Value, sizeof(int32_t));
        out.Value = htonf(out.Value);
        return sock;
    }
};

typedef SocketByte SocketAngle;

class SocketPosition {
public:
    uint64_t Value;

    SocketPosition() : Value(0) { }
    SocketPosition(int32_t x, int16_t y, int32_t z) { SetValue(x, y, z); }

    int32_t GetX() {
        return Value >> 38;
    }

    int32_t GetY() {
        return Value & 0xFFF;
    }

    int32_t GetZ() {
        return Value << 26 >> 38;
    }

    void SetValue(int32_t x, int16_t y, int32_t z) {
        Value = ((x & 0x3FFFFFF) << 38) | ((z & 0x3FFFFFF) << 12) | (y & 0xFFF);
    }

    friend SocketOStream& operator<<(SocketOStream& sock, const SocketPosition& out) {
        sock.Write((const char*)&out.Value, sizeof(uint64_t));
        return sock;
    }

    friend SocketIStream& operator>>(SocketIStream& sock, SocketPosition& out) {
        sock.Read((char*)&out.Value, sizeof(uint64_t));
        return sock;
    }
};

typedef SocketString SocketNBT; // for now, it seems fine to me rn
typedef SocketString SocketEntityMetadata; // for now, it seems fine to me rn

class SocketNode {
public:
    SocketByte Flags;
    std::vector<SocketVarInt> ChildIndices;
    std::optional<SocketVarInt> RedirNode;
    std::optional<SocketString> Name;
    std::optional<SocketIdentifier> Parser;
    std::optional<SocketString> Properties; // actually varies, intend this as a byte array as placeholder (https://wiki.vg/Command_Data#Parsers)
    std::optional<SocketIdentifier> SuggestionType;

    SocketNode() : Flags(0) { }

    friend SocketOStream& operator<<(SocketOStream& sock, const SocketNode& out) {
        sock << out.Flags << SocketVarInt(out.ChildIndices.size());
        for (auto& ind : out.ChildIndices) {
            sock << ind;
        }
        if (out.Flags & 0x08) {
            sock << out.RedirNode.value();
        }
        if ((out.Flags & 0x03) == 2 || (out.Flags & 0x03) == 1) {
            sock << out.Name.value();
        }
        if ((out.Flags & 0x03) == 2) {
            sock << out.Parser.value();
            sock << out.Properties.value();
            if (out.Flags & 0x10) {
                sock << out.SuggestionType.value();
            }
        }
        return sock;
    }

    /*
    Not intended to be read, why would a client send it?
    friend SocketIStream& operator>>(SocketIStream& sock, SocketNode& out) {
        return sock;
    }
    */
};

class SocketSlot {
public:
    SocketBool Present;
    std::optional<SocketVarInt> ItemId;
    std::optional<SocketByte> Count;
    std::optional<SocketNBT> NbtData;

    SocketSlot() : Present(false) { }

    friend SocketOStream& operator<<(SocketOStream& sock, const SocketSlot& out) {
        sock << out.Present;
        if (out.Present) {
            sock << out.ItemId.value() << out.Count.value() << out.NbtData.value();
        }
        return sock;
    }

    friend SocketIStream& operator>>(SocketIStream& sock, SocketSlot& out) {
        sock >> out.Present;
        if (out.Present) {
            sock >> out.ItemId.emplace() >> out.Count.emplace() >> out.NbtData.emplace();
        }
        return sock;
    }
};

// basically SocketString but doesn't append length
class SocketVaries {
public:
    SocketVarInt Length;
    std::unique_ptr<char[]> Data;

    SocketVaries() : Length(0) { }
    SocketVaries(std::string& val) { SetValue(val); }
    operator std::string& () { return std::string(Data.get(), Data.get() + Length); }
    operator std::string() const { return std::string(Data.get(), Data.get() + Length); }

    SocketVaries(const char* data) {
        Length = strlen(data);
        Data = std::make_unique<char[]>(Length + 1);
        memcpy(Data.get(), data, Length.Value + 1);
    }

    void SetValue(const std::string& str) {
        Length = str.size();
        Data.reset(new char[Length + 1]);
        memcpy(Data.get(), str.data(), Length);
        Data[Length] = '\0';
    }

    friend SocketOStream& operator<<(SocketOStream& sock, const SocketVaries& out) {
        sock.Write(out.Data.get(), out.Length);
        return sock;
    }

    friend SocketIStream& operator>>(SocketIStream& sock, SocketVaries& out) {
        out.Data = std::make_unique<char[]>(out.Length);
        sock.Read(out.Data.get(), out.Length);
        return sock;
    }
};