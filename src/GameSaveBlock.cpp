#include "GameSaveBlock.h"
#include "Sections.h"
#include "Binary.h"

#include <iostream>

GameSaveBlock::GameSaveBlock(char* data)
{
	char sectionData[SectionSize];
	u16 id, checksum;
	u32 index;
	for (u8 i = 0; i < NumOfSections; i++)
	{
		id = getBytes<u16>(data, 0x0FF4);
		checksum = getBytes<u16>(data, 0x0FF6);
		index = getBytes<u32>(data, 0x0FFC);

		std::copy(data + i * SectionSize, data + (i + 1) * SectionSize, sectionData);

		if (id == 1)
		{
			trainerData = new Section<TrainerInfo>(sectionData, id, checksum, index);
		}
	}
}

GameSaveBlock::~GameSaveBlock()
{
	delete trainerData;
}
