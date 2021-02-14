#include "GameSaveBlock.h"
#include "Binary.h"

#include <iostream>

GameSaveBlock::GameSaveBlock(char* data)
{
	char sectionData[SectionSize];
	u8 id, checksum;
	u32 index;
	for (u8 i = 0; i < NumOfSections; i++)
	{
		std::copy(data + i * SectionSize, data + (i + 1) * SectionSize, sectionData);

		id = getByte(sectionData, 0x0FF4);
		checksum = getBytes<u16>(sectionData, 0x0FF6);
		index = getBytes<u32>(sectionData, 0x0FFC);

		if (id == 0 && !trainerData)
		{
			trainerData = new Section<TrainerInfo>(sectionData, id, checksum, index);
		}
	}
}

GameSaveBlock::~GameSaveBlock()
{
	delete trainerData;
}
