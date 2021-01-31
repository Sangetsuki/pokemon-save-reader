#include "GameSaveBlock.h"
#include "Sections.h"
#include "Save.h"

Save::Save(const char* path)
{
	std::ifstream data(path, std::ios::in | std::ios::binary);
	data.read(bytes, TotalSize);
	data.close();
	file.open(path, std::ios::out | std::ios::binary);

	SaveBlock = new GameSaveBlock(bytes, this);
};

Save::~Save()
{
	saveFile();
	file.close();
	delete SaveBlock;
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

void Save::saveFile()
{
	file.write(bytes, TotalSize);
};
