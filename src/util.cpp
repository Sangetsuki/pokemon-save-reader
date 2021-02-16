#include "util.h"

char PokeToAscii(u8 target)
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