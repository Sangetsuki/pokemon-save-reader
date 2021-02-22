#include "Pokemon.h"
#include "Binary.h"
#include "util.h"
#include <iostream>
#include <bitset>

void decrypt(char* data, u32 PID, u32 TID)
{
	u32 key = PID ^ TID;
	char decrypted[12];

	for (u8 i = 0; i < 12; i++)
	{
		decrypted[i] = (key ^ getBytes<u32>(data, i / 4)) >> (8 * i);
	}

	std::copy(decrypted, decrypted + 12, data);
}

u16 getGrowthOffset(u32 PID)
{
	u8 order = PID % 24;
	u16 offset;
	switch (order)
	{
		case 0 ... 5:
			offset = 0;
			break;
		case 6: case 7: case 12: case 13: case 18: case 19:
			offset = 1;
			break;
		case 8: case 10: case 14: case 16: case 20: case 22:
			offset = 2;
			break;
		default:
			offset = 3;
	}
	return 32 + 12 * offset;
}

u16 getAttacksOffset(u32 PID)
{
	u8 order = PID % 24;
	u16 offset;
	switch (order)
	{
		case 6 ... 11:
			offset = 0;
			break;
		case 0: case 1: case 14: case 15: case 20: case 21:
			offset = 1;
			break;
		case 2: case 4: case 12: case 17: case 18: case 23:
			offset = 2;
			break;
		default:
			offset = 3;
	}
	return 32 + 12 * offset;
}

u16 getConditionOffset(u32 PID)
{
	u8 order = PID % 24;
	u16 offset;
	switch (order)
	{
		case 12 ... 17:
			offset = 0;
			break;
		case 2: case 3: case 8: case 9: case 22: case 23:
			offset = 1;
			break;
		case 0: case 5: case 6: case 11: case 19: case 21:
			offset = 2;
			break;
		default:
			offset = 3;
	}
	return 32 + 12 * offset;
}

u16 getMiscOffset(u32 PID)
{
	u8 order = PID % 24;
	u16 offset;
	switch (order)
	{
		case 18 ... 23:
			offset = 0;
			break;
		case 4: case 5: case 10: case 11: case 16: case 17:
			offset = 1;
			break;
		case 1: case 3: case 7: case 9: case 13: case 15:
			offset = 2;
			break;
		default:
			offset = 3;
	}
	return 32 + 12 * offset;
}

PokemonMisc::PokemonMisc(char* _data)
{
	u32 PID = getBytes<u32>(_data, 00);
	u32 TID = getBytes<u32>(_data, 04);
	u16 offset = getMiscOffset(PID);

	char data[12];
	std::copy(_data + offset, _data + offset + 12, data);
	decrypt(data, PID, TID);

	pokerus = getByte(data, 0);
	met = getByte(data, 1);
	origin = getBytes<u16>(data, 2);
	u32 iea = getBytes<u32>(data, 4);

	for (u8 i = 0; i < 6; i++)
	{
		IV[i] = iea & (0x1F << (i * 5));
	}

	egg = (iea >> 30) & 0x01;
	ability = iea >> 31;

	std::cout << std::bitset<32>(iea) << std::endl;
}

PokemonGrowth::PokemonGrowth(char* _data)
{
	u32 PID = getBytes<u32>(_data, 00);
	u32 TID = getBytes<u32>(_data, 04);
	u16 offset = getGrowthOffset(PID);

	char data[12];
	std::copy(_data + offset, _data + offset + 12, data);
	decrypt(data, PID, TID);

	species = getBytes<u16>(data, 0);
	item = getBytes<u16>(data, 2);
	xp = getBytes<u32>(data, 4);
	PP = getByte(data, 8);
	friendship = getByte(data, 9);
}

PokemonAttacks::PokemonAttacks(char* _data)
{
	u32 PID = getBytes<u32>(_data, 00);
	u32 TID = getBytes<u32>(_data, 04);
	u16 offset = getAttacksOffset(PID);

	char data[12];
	std::copy(_data + offset, _data + offset + 12, data);
	decrypt(data, PID, TID);

	for (u8 i = 0; i < 4; i++)
	{
		moves[i] = getBytes<u16>(data, 2 * i);
		pp[i] = getByte(data, 8 + i);
	}
}

PokemonCondition::PokemonCondition(char* _data)
{
	u32 PID = getBytes<u32>(_data, 00);
	u32 TID = getBytes<u32>(_data, 04);
	u16 offset = getConditionOffset(PID);

	char data[12];
	std::copy(_data + offset, _data + offset + 12, data);
	decrypt(data, PID, TID);

	for (u8 i = 0; i < 6; i++)
	{
		EV[i] = getByte(data, i);
	}

	for (u8 i = 0; i < 5; i++)
	{
		contest[i] = getByte(data, i + 6);
	}
	
	Feel = getByte(data, 11);
}

Pokemon::Pokemon(char* data) : growth(data), attacks(data), condition(data), misc(data)
{
	PID = getBytes<u32>(data, 00);

	TID = getBytes<u32>(data, 04);

	for (u8 i = 0; i < 10; i++)
	{
		Nickname[i] = PokeToAscii(getByte(data, 8 + i));
	}

	for (u8 i = 0; i < 7; i++)
	{
		Tname[i] = PokeToAscii(getByte(data, 20 + i));
	}

	Language = getBytes<u16>(data, 18);
	markings = getByte(data, 27);
	Checksum = getBytes<u16>(data, 28);

 	unknown = getBytes<u16>(data, 30);

	Status = getBytes<u32>(data, 80);

	Level = getByte(data, 84);

	Pokerus = getByte(data, 85);

	CurrentHP = getBytes<u16>(data, 86);

	for (u8 i = 0; i < 6; i++)
	{
		stats[i] = getBytes<u16>(data, 88 + 2 * i);
	}
}
