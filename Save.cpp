#include "Save.h"
#include <iostream>

Save::Save(const char* path)
{
	std::ifstream data(path, std::ios::in | std::ios::binary);
	data.read(bytes, TotalSize);
	data.close();
	file.open(path, std::ios::out | std::ios::binary);
};

Save::~Save()
{
	saveFile();
	file.close();
};

uint16_t Save::getSaveBlockOffset()
{
	uint32_t SaveBlockAIndex = getByte(0x0FFC);
	uint32_t SaveBlockBIndex = getByte(GameSaveASize + 0x0FFC);

	return SaveBlockAIndex > SaveBlockBIndex ? 0x0000 : GameSaveASize;
};

uint16_t Save::getSection(uint8_t id)
{
	uint16_t result;
	uint16_t start = getSaveBlockOffset();

	for (uint8_t i = 0; i < NumOfSections; i++)
	{
		uint8_t currentId = getByte(start + i * SectionSize + 0x0FF4);
		if (currentId == id)
		{
			result = start + i * SectionSize;
		}
	}
	return result;
};

char* Save::getPlayerName(char* target)
{
	uint16_t trainerData = getSection(0);
	for (uint16_t i = 0x0000; i < 0x0008; i++)
	{
		uint32_t pokeHex = getByte(trainerData + i);
		target[i] = convertToAscii(pokeHex);
	}
	return target;
};

uint16_t Save::getPlayerGender()
{
	uint16_t trainerData = getSection(0);
	uint32_t gender = getByte(trainerData + 0x0008);
	return gender;
};

uint32_t Save::convertToAscii(uint32_t id)
{
	uint8_t result;
	switch(id)
	{
		case 0x00:
			result = 32;
			break;
		case 0xA1 ... 0xAA: // NUMBERS
			result = id - 113;
			break;
		case 0xBB ... 0xD4: // UPPER CASE
			result = id - 122;
			break;
		case 0xD5 ... 0xEE: // LOWER CASE
			result = id - 116;
			break;
		case 0xFF:	default: // ANYTHING ELSE
			result = 0;
	};

	return result;
};

uint16_t Save::getPlayerSID()
{
	uint16_t location = getSection(0) + 0x000C;
	uint32_t result = getBytes(location, 2);;
	return result;
};

uint16_t Save::getPlayerID()
{
	uint16_t location = getSection(0) + 0x000A;
	uint32_t result = getBytes(location, 2);;
	return result;
};

uint32_t Save::getByte(uint16_t offset)
{
	return ((uint32_t)bytes[offset]) & 0xFF;
}

uint32_t Save::getBytes(uint16_t offset, uint16_t size)
{
	uint32_t result = 0;
	for (uint8_t i = 0; i < size; i++)
	{
		result |= getByte(offset + i) << (8 * i);
	}
	return result;
}

uint32_t Save::getPlayerGame()
{
	uint16_t location = getSection(0) + 0x00AC;
	uint32_t result = getByte(location);
	if (result != 0 && result != 1)
	{
		return 2;
	}
	return result;
};

uint32_t Save::getPlayerSecret()
{
	uint16_t location = getSection(0);
	uint32_t result;
	switch(getPlayerGame())
	{
		case 0:
			result = 0;
			break;
		case 1:
			location += 0x0AF8;
			result = getBytes(location, 4);
			break;
		case 2:
			location += 0x00AC;
			result = getBytes(location, 4);
			break;
	};
	return result;
};

uint32_t Save::getPlayerMoney()
{
	uint16_t location = getSection(1) + 0x0490;
	uint32_t money = getBytes(location, 4);
	uint32_t secret = getPlayerSecret();

	return money ^ secret;
};

uint32_t Save::setPlayerMoney(uint32_t amount)
{
	uint32_t amountXOR = amount ^ getPlayerSecret();
	uint16_t location = getSection(1) + 0x0490;

	setBytes(location, amountXOR, 4);

	return getPlayerMoney();
};

uint32_t Save::setByte(uint16_t offset, uint32_t newByte)
{
	bytes[offset] = newByte;
	return getByte(offset);
};

uint32_t Save::setBytes(uint16_t offset, uint32_t newBytes, uint16_t size)
{
	for (uint16_t i = 0; i < size; i++)
	{
		bytes[offset + i] = (newBytes >> (8 * i)) & 0xFF;
	}
	return getBytes(offset, size);
};

uint16_t Save::setPlayerGender(uint16_t newGender)
{
	uint16_t offset = getSection(0) + 0x0008;
	uint32_t gender = newGender % 2; // 0 or 1
	setByte(offset, gender);
	return getPlayerGender();
};

void Save::saveFile()
{
	/*for (uint8_t i = 0; i < NumOfSections; i++)
	{
		uint16_t secAcs = genChecksum(i, 0);
		setBytes(getSection(i, 0), secAcs, 2);

		uint16_t secBcs = genChecksum(i, 1);
		setBytes(getSection(i, 1), secBcs, 2);
	}*/
	file.write(bytes, TotalSize);
};
