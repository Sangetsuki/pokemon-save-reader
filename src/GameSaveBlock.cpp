#include "GameSaveBlock.h"
#include "Sections.h"

#include <iostream>

GameSaveBlock::GameSaveBlock(char* data)
{
	char sectionData[SectionSize];

	for (u8 i = 0; i < NumOfSections; i++)
	{
		std::copy(data + i * SectionSize, data + (i + 1) * SectionSize, sectionData);

		u16 id = getBytes<u16>(sectionData, 0x0FF4);

		switch (id)
		{
			case 0:
				trainerData = new TrainerInfo(sectionData);
				break;
			case 1:
				inv = new TrainerInventory(sectionData);
				break;
			default:
				break;
		}
	}
}

GameSaveBlock::~GameSaveBlock()
{
	delete trainerData;
	delete inv;
}
