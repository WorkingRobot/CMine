#pragma once

#include <WinSock2.h>

#include <istream>
#include <memory>
#include <unordered_map>
#include <variant>
#include <vector>

enum class NBTType : uint8_t {
	End,
	Byte,
	Short,
	Int,
	Long,
	Float,
	Double,
	ByteArray,
	String,
	List,
	Compound,
	IntArray,
	LongArray
};

struct NBTByte;
struct NBTShort;
struct NBTInt;
struct NBTLong;
struct NBTFloat;
struct NBTDouble;
struct NBTByteArray;
struct NBTString;
struct NBTList;
struct NBTCompound;
struct NBTIntArray;
struct NBTLongArray;

typedef std::variant<NBTByte, NBTShort, NBTInt, NBTLong, NBTFloat, NBTDouble, NBTByteArray, NBTString, NBTList, NBTCompound, NBTIntArray, NBTLongArray> NBTItem;

bool ReadItem(std::istream& inp, NBTItem& out, NBTType type);
void PrintDocument(std::ostream& cout, const NBTCompound& inp);

struct NBTByte {
public:
	int8_t Value;

	NBTByte() : Value(0) { }
	NBTByte(int8_t val) : Value(val) { }
	operator int8_t& () { return Value; }
	operator int8_t() const { return Value; }

	friend std::istream& operator>>(std::istream& inp, NBTByte& out);
};

struct NBTShort {
public:
	int16_t Value;

	NBTShort() : Value(0) { }
	NBTShort(int16_t val) : Value(val) { }
	operator int16_t& () { return Value; }
	operator int16_t() const { return Value; }

	friend std::istream& operator>>(std::istream& inp, NBTShort& out);
};

struct NBTInt {
public:
	int32_t Value;

	NBTInt() : Value(0) { }
	NBTInt(int32_t val) : Value(val) { }
	operator int32_t& () { return Value; }
	operator int32_t() const { return Value; }

	friend std::istream& operator>>(std::istream& inp, NBTInt& out);
};

struct NBTLong {
public:
	int64_t Value;

	NBTLong() : Value(0) { }
	NBTLong(int64_t val) : Value(val) { }
	operator int64_t& () { return Value; }
	operator int64_t() const { return Value; }

	friend std::istream& operator>>(std::istream& inp, NBTLong& out);
};

struct NBTFloat {
public:
	float_t Value;

	NBTFloat() : Value(0) { }
	NBTFloat(float_t val) : Value(val) { }
	operator float_t& () { return Value; }
	operator float_t() const { return Value; }

	friend std::istream& operator>>(std::istream& inp, NBTFloat& out);
};

struct NBTDouble {
public:
	double_t Value;

	NBTDouble() : Value(0) { }
	NBTDouble(double_t val) : Value(val) { }
	operator double_t& () { return Value; }
	operator double_t() const { return Value; }

	friend std::istream& operator>>(std::istream& inp, NBTDouble& out);
};

struct NBTByteArray {
public:
	NBTInt Length;
	std::unique_ptr<char[]> Data;

	NBTByteArray() : Length(0) { }

	friend std::istream& operator>>(std::istream& inp, NBTByteArray& out);
};

struct NBTString {
public:
	NBTInt Length;
	std::unique_ptr<char[]> Data;

	NBTString() { }

	friend std::ostream& operator<<(std::ostream& out, const NBTString& str) {
		return out.write(str.Data.get(), str.Length);
	}

	friend std::istream& operator>>(std::istream& inp, NBTString& out);
};

struct NBTList {
public:
	NBTType ItemType;
	std::vector<NBTItem> Items;

	friend std::istream& operator>>(std::istream& inp, NBTList& out);
};

struct NBTCompound {
public:
	std::vector<std::shared_ptr<std::pair<NBTString, NBTItem>>> Items;

	friend std::istream& operator>>(std::istream& inp, NBTCompound& out);
};

struct NBTIntArray {
public:
	std::vector<NBTInt> Value;

	friend std::istream& operator>>(std::istream& inp, NBTIntArray& out);
};

struct NBTLongArray {
public:
	std::vector<NBTLong> Value;

	friend std::istream& operator>>(std::istream& inp, NBTLongArray& out);
};