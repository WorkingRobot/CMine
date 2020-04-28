#include "FileWorld.h"

#include <iostream>
#include <fstream>

FileWorld::FileWorld(fs::path worldPath)
{
	NBTDocument doc;
	auto serverDat = fs::path(getenv("APPDATA")) / ".minecraft" / "servers.dat";
	std::fstream servers(serverDat, std::ios_base::in | std::ios_base::binary);
	servers >> doc;
	PrintItem(std::cout, doc);
}

FileWorld::~FileWorld()
{
}
