#include "NbtTypes.h"

#include <iomanip>

bool ReadItem(std::istream& inp, NBTItem& out, NBTType type)
{
	switch (type)
	{
	case NBTType::Byte:
	{
		NBTByte value;
		inp >> value;
		out = value;
		return true;
	}
	case NBTType::Short:
	{
		NBTShort value;
		inp >> value;
		out = value;
		return true;
	}
	case NBTType::Int:
	{
		NBTInt value;
		inp >> value;
		out = value;
		return true;
	}
	case NBTType::Long:
	{
		NBTLong value;
		inp >> value;
		out = value;
		return true;
	}
	case NBTType::Float:
	{
		NBTFloat value;
		inp >> value;
		out = value;
		return true;
	}
	case NBTType::Double:
	{
		NBTDouble value;
		inp >> value;
		out = value;
		return true;
	}
	case NBTType::ByteArray:
	{
		NBTByteArray value;
		inp >> value;
		out = std::move(value);
		return true;
	}
	case NBTType::String:
	{
		NBTString value;
		inp >> value;
		out = value;
		return true;
	}
	case NBTType::List:
	{
		NBTList value;
		inp >> value;
		out = std::move(value);
		return true;
	}
	case NBTType::Compound:
	{
		NBTCompound value;
		inp >> value;
		out = std::move(value);
		return true;
	}
	case NBTType::IntArray:
	{
		NBTIntArray value;
		inp >> value;
		out = value;
		return true;
	}
	case NBTType::LongArray:
	{
		NBTLongArray value;
		inp >> value;
		out = value;
		return true;
	}
	}
	return false;
}

constexpr NBTType GetType(const NBTItem& inp) {
	return std::visit<NBTType>([](auto&& arg) {
		using T = std::decay_t<decltype(arg)>;
		if constexpr (std::is_same_v<T, NBTByte>)
			return NBTType::Byte;
		else if constexpr (std::is_same_v<T, NBTShort>)
			return NBTType::Short;
		else if constexpr (std::is_same_v<T, NBTInt>)
			return NBTType::Int;
		else if constexpr (std::is_same_v<T, NBTLong>)
			return NBTType::Long;
		else if constexpr (std::is_same_v<T, NBTFloat>)
			return NBTType::Float;
		else if constexpr (std::is_same_v<T, NBTDouble>)
			return NBTType::Double;
		else if constexpr (std::is_same_v<T, NBTByteArray>)
			return NBTType::ByteArray;
		else if constexpr (std::is_same_v<T, NBTString>)
			return NBTType::String;
		else if constexpr (std::is_same_v<T, NBTList>)
			return NBTType::List;
		else if constexpr (std::is_same_v<T, NBTCompound>)
			return NBTType::Compound;
		else if constexpr (std::is_same_v<T, NBTIntArray>)
			return NBTType::IntArray;
		else if constexpr (std::is_same_v<T, NBTLongArray>)
			return NBTType::LongArray;
		else
			return NBTType::End;
	}, inp);
}

inline const char* GetTypeString(NBTType type) {
	switch (type)
	{
	case NBTType::End:
		return "TAG_End";
	case NBTType::Byte:
		return "TAG_Byte";
	case NBTType::Short:
		return "TAG_Short";
	case NBTType::Int:
		return "TAG_Int";
	case NBTType::Long:
		return "TAG_Long";
	case NBTType::Float:
		return "TAG_Float";
	case NBTType::Double:
		return "TAG_Double";
	case NBTType::ByteArray:
		return "TAG_Byte_Array";
	case NBTType::String:
		return "TAG_String";
	case NBTType::List:
		return "TAG_List";
	case NBTType::Compound:
		return "TAG_Compound";
	case NBTType::IntArray:
		return "TAG_Int_Array";
	case NBTType::LongArray:
		return "TAG_Long_Array";
	}
}

inline void PrintTabs(std::ostream& out, int tabCount) {
	for (; tabCount; --tabCount)
		out << "  ";
}

inline void PrintItemInternal(std::ostream& cout, const NBTItem& inp, NBTType type, int tab) {
	switch (type)
	{
	case NBTType::Byte:
		cout << std::get<NBTByte>(inp).Value;
		break;
	case NBTType::Short:
		cout << std::get<NBTShort>(inp).Value;
		break;
	case NBTType::Int:
		cout << std::get<NBTInt>(inp).Value;
		break;
	case NBTType::Long:
		cout << std::get<NBTLong>(inp).Value;
		break;
	case NBTType::Float:
		cout << std::get<NBTFloat>(inp).Value;
		break;
	case NBTType::Double:
		cout << std::get<NBTDouble>(inp).Value;
		break;
	case NBTType::ByteArray:
	{
		auto& arr = std::get<NBTByteArray>(inp);

		cout << arr.Length << " bytes\n";
		PrintTabs(cout, tab + 1);
		cout << "[ ";

		char const hex_chars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
		for (int i = 0; i < arr.Length; ++i)
		{
			auto& byte = arr.Data[i];

			cout << hex_chars[(byte & 0xF0) >> 4];
			cout << hex_chars[(byte & 0x0F) >> 0];
		}

		cout << " ]";
	}
	break;
	case NBTType::String:
		cout << "\"" << std::get<NBTString>(inp).Value << "\"";
		break;
	case NBTType::List:
	{
		auto& arr = std::get<NBTList>(inp);

		cout << arr.Items.size() << " of " << GetTypeString(arr.ItemType) << "\n";
		PrintTabs(cout, tab);
		cout << "{\n";

		for (auto& v : arr.Items) {
			PrintTabs(cout, tab + 1);
			PrintItemInternal(cout, v, arr.ItemType, tab + 1);
			cout << '\n';
		}

		PrintTabs(cout, tab);
		cout << "}";
	}
	break;
	case NBTType::Compound:
	{
		auto& cmp = std::get<NBTCompound>(inp);

		cout << cmp.Items.size() << " entries\n";
		PrintTabs(cout, tab);
		cout << "{\n";

		
		for (auto& item : cmp.Items) {
			PrintTabs(cout, tab + 1);
			auto itemType = GetType(*item.second);
			cout << GetTypeString(itemType) << "('" << item.first.Value << "'): ";
			PrintItemInternal(cout, *item.second, itemType, tab + 1);
			cout << '\n';
		}

		PrintTabs(cout, tab);
		cout << "}";
	}
	break;
	case NBTType::IntArray:
	{
		auto& arr = std::get<NBTIntArray>(inp);

		cout << arr.Value.size() << " ints\n";
		PrintTabs(cout, tab);
		cout << "{\n";

		PrintTabs(cout, tab + 1);
		for (auto& v : arr.Value) {
			cout << v.Value << ', ';
		}

		cout << "\n";
		PrintTabs(cout, tab);
		cout << "}";
	}
	break;
	case NBTType::LongArray:
	{
		auto& arr = std::get<NBTLongArray>(inp);

		cout << arr.Value.size() << " longs\n";
		PrintTabs(cout, tab);
		cout << "{\n";

		PrintTabs(cout, tab + 1);
		for (auto& v : arr.Value) {
			cout << v.Value << ', ';
		}

		cout << "\n";
		PrintTabs(cout, tab);
		cout << "}";
	}
	break;
	default:
		break;
	}
}

void PrintItem(std::ostream& cout, const NBTCompound& inp)
{
	PrintItemInternal(cout, inp, NBTType::Compound, 0);
}

inline std::istream& operator>>(std::istream& inp, NBTByte& out)
{
    return inp.read((char*)&out.Value, 1);
}

inline std::istream& operator>>(std::istream& inp, NBTShort& out) {
	inp.read((char*)&out.Value, 2);
	out.Value = ntohs(out.Value);
	return inp;
}

inline std::istream& operator>>(std::istream& inp, NBTInt& out) {
	inp.read((char*)&out.Value, 4);
	out.Value = ntohl(out.Value);
	return inp;
}

inline std::istream& operator>>(std::istream& inp, NBTLong& out) {
	inp.read((char*)&out.Value, 8);
	out.Value = ntohll(out.Value);
	return inp;
}

inline std::istream& operator>>(std::istream& inp, NBTFloat& out) {
	uint32_t Value;
	inp.read((char*)&Value, 4);
	out.Value = ntohf(Value);
	return inp;
}

inline std::istream& operator>>(std::istream& inp, NBTDouble& out) {
	uint64_t Value;
	inp.read((char*)&Value, 8);
	out.Value = ntohd(Value);
	return inp;
}

inline std::istream& operator>>(std::istream& inp, NBTByteArray& out) {
	inp >> out.Length;
	out.Data = std::make_unique<char[]>(out.Length);
	inp.read(out.Data.get(), out.Length);
	return inp;
}

inline std::istream& operator>>(std::istream& inp, NBTString& out) {
	uint16_t Length;
	inp.read((char*)&Length, 2);
	Length = ntohs(Length);

	out.Value.reserve(Length);
	auto buffer = std::make_unique<char[]>(Length);
	inp.read(buffer.get(), Length);
	out.Value.append(buffer.get(), Length);
	return inp;
}

inline std::istream& operator>>(std::istream& inp, NBTList& out) {
	NBTByte type;
	NBTInt Length;
	inp >> type >> Length;
	out.ItemType = (NBTType)type.Value;

	out.Items.reserve(Length);
	NBTItem item;
	for (int i = 0; i < Length; ++i) {
		if (ReadItem(inp, item, out.ItemType)) {
			out.Items.emplace_back(std::move(item));
		}
	}
	return inp;
}

std::istream& operator>>(std::istream& inp, NBTCompound& out) {
	NBTType Type;
	NBTString Key;
	while (true) {
		NBTByte type;
		inp >> type;
		Type = (NBTType)type.Value;

		if (Type == NBTType::End) {
			break;
		}

		inp >> Key;

		auto value = std::make_shared<NBTItem>();
		if (ReadItem(inp, *value, Type)) {
			out.Items.emplace_back(Key, value);
		}
	}
	return inp;
}

inline std::istream& operator>>(std::istream& inp, NBTIntArray& out) {
	NBTInt Length;
	inp >> Length;
	out.Value.reserve(Length);
	NBTInt Value;
	for (int i = 0; i < Length; ++i) {
		inp >> Value;
		out.Value.emplace_back(Value);
	}
	return inp;
}

inline std::istream& operator>>(std::istream& inp, NBTLongArray& out) {
	NBTInt Length;
	inp >> Length;
	out.Value.reserve(Length);
	NBTLong Value;
	for (int i = 0; i < Length; ++i) {
		inp >> Value;
		out.Value.emplace_back(Value);
	}
	return inp;
}