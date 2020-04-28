#pragma once

#include "../nbt/NbtDocument.h"

#include <filesystem>
namespace fs = std::filesystem;

class FileWorld {
public:
	FileWorld(fs::path worldPath);
	~FileWorld();

private:

};