#include "Sections.h"
#include <iostream>
#include "util.h"

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
	partySize = getBytes<u32>(data, 0x0234);
	money = getBytes<u32>(data, 0x0490);
}