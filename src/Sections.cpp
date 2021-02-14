#include "Sections.h"
#include "Binary.h"
#include <iostream>

TrainerInfo::TrainerInfo(char* data)
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

char TrainerInfo::PokeToAscii(u8 target)
{
	char result;
	switch(target)
	{
		case 0x00: // SPACE
			result = 32;
			break;
		case 0xA1 ... 0xAA: // NUMBERS
			result = target - 113;
			break;
		case 0xBB ... 0xD4: // UPPER CASE
			result = target - 122;
			break;
		case 0xD5 ... 0xEE: // LOWER CASE
			result = target - 116;
			break;
		case 0xFF:	default: // ANYTHING ELSE
			result = 0;
	};
	return result;
}