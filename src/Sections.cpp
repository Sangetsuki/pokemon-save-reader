#include "Sections.h"
#include "Pokemon.h"
#include <iostream>
#include "util.h"

Section::Section(char* data)
{
	std::copy(data, data + 0x1000, bytes);
	id = getBytes<u16>(bytes, 0x0FF4);
	checksum = getBytes<u16>(bytes, 0x0FF6);
	index = getBytes<u32>(bytes, 0x0FFC);
}

u32 Section::updateChecksum()
{
	u32 result = 0; // initializate an u32 to 0
	for (u32 i = 0; i < 0X03E0; i++)
	{
		u32 w = getBytes<u32>(bytes, 4 * i); // 4 bytes at a time
		result += w; // sum them to the result
	}
	result = (result >> 16) + (result & 0xFF); // upper 2 bytes + lower 2 bytes
	setBytes<u16>(bytes, 0x0FF6, result);
	checksum = getBytes<u16>(bytes, 0x0FF6);
	return checksum;
}

TrainerInfo::TrainerInfo(char* data) : Section(data)
{
	for (u8 i = 0; i < 8; i++)
	{
		name[i] = PokeToAscii(getByte(data, 0x0000 + i)); // needs to be converted to ascii
	}

	gender = getByte(data, 0x0008);
	TID = getBytes<u16>(data, 0x000A);
	SID = getBytes<u16>(data, 0x000C);
	secret = getBytes<u32>(data, 0x00AC);
}

TrainerInventory::TrainerInventory(char* data) : Section(data)
{
	char pokemon[0x100];
	for (u8 i = 0; i <= getpartySize(); i++)
	{
		u16 offset = 0x0238 + 100 * i;
		std::copy(data + offset, data + offset + 0x100, pokemon);
	
		party[i] = new Pokemon(pokemon);
	}
}

TrainerInventory::~TrainerInventory()
{
	for (u8 i = 0; i <= getpartySize(); i++)
	{
		delete party[i];
	}
}

u32 TrainerInventory::getpartySize()
{
	return getBytes<u32>(bytes, 0x0234);
}

u32 TrainerInventory::getMoney()
{
	return getBytes<u32>(bytes, 0x0490);
}

u32 TrainerInventory::setMoney(u32 money)
{
	return setBytes<u32>(bytes, 0x0490, money);
}
