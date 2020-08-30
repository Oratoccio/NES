#include "ines.hpp"

#include <cstring>
#include <fstream>
#include <string>

bool nes::INES::LoadFromDisk(std::string_view path)
{
	std::ifstream rom(path.data(), std::ios_base::in | std::ios_base::binary);
	if (!rom.is_open())
	{
		return false;
	}

	// Determine file size
	rom.seekg(0, std::ios_base::end);
	size_t romSize = rom.tellg();
	rom.seekg(0, std::ios_base::beg);

	// Dump the file into memory
	RawData.resize(romSize, 0);
	rom.read(reinterpret_cast<char*>(RawData.data()), romSize);
	rom.close();

	return true;
}

bool nes::INES::IsValidRom() const
{
	std::uint8_t magicNumber[5];
	std::memcpy(magicNumber, RawData.data(), 5);

	return std::strcmp(reinterpret_cast<char*>(magicNumber), "NES^Z");
}

const std::vector<std::uint8_t>& nes::INES::GetRaw() const
{
	return RawData;
}
