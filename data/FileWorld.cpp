#include "FileWorld.h"

#include "../zstr.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

FileWorld::FileWorld(fs::path worldPath)
{
	NBTDocument doc;
	{
		// also tested against all examples in https://wiki.vg/NBT#Download
		fs::path serverDat = fs::path(getenv("APPDATA")) / ".minecraft" / "servers.dat";
		zstr::ifstream servers(serverDat.string(), std::ios::binary);
		servers >> doc;
	}
	std::ostringstream docOut; // prevents slowdowns that can sometimes happen
	docOut.precision(10000); // prevents scientific notation
	PrintDocument(std::cout, doc);
	std::cout << docOut.str();
}

FileWorld::~FileWorld()
{
}
