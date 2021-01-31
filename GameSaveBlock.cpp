#include "GameSaveBlock.h"
#include "Sections.h"
#include "Save.h"

#include <iostream>

GameSaveBlock::GameSaveBlock(char* data, Save* save)
{
	for (uint8_t i = 0; i < NumOfSections; i++)
	{
		uint16_t secI = save->getSection(i);

		char secData[SectionSize];
		uint16_t id, checksum;
		uint32_t index;

		memcpy(secData, &data, SectionSize);
		id = save->getBytes(secI + 0x0FF4, 2);
		checksum = save->getBytes(secI + 0x0FF6, 2);
		index = save->getBytes(secI + 0x0FFC, 4);

		if (id == 0)
		{
			sections[i] = new TrainerInfo(secData, id, checksum, index, this);
		} else {
			sections[i] = new Section(secData, id, checksum, index, this);
		}
		
	}
	saveFile = save;
}

GameSaveBlock::~GameSaveBlock()
{
	for (uint8_t i = 0; i < NumOfSections; i++)
	{
		delete sections[i];
	}	
}

Section* GameSaveBlock::getSection(uint16_t id)
{
	return sections[id % NumOfSections];
}
