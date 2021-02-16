#include "GameSaveBlock.h"
#include "Sections.h"

#include <iostream>

GameSaveBlock::GameSaveBlock(char* data) // data size is GameSaveASize = 0xE000
{
	std::copy(data, data + GameSaveASize, bytes);
	char sectionData[SectionSize];

	for (u8 i = 0; i < NumOfSections; i++)
	{
		std::copy(data + i * SectionSize, data + (i + 1) * SectionSize, sectionData);

		u16 id = getBytes<u16>(sectionData, 0x0FF4);

		// im sorry
		switch (id)
		{
			case 0:
				trainer = new TrainerInfo(sectionData);
				break;
			case 1:
				inv = new TrainerInventory(sectionData);
				break;
			default:
				/*Section* ptr = new Section(sectionData);
				sections[i] = &ptr;*/
				break;
		}
	}
}

GameSaveBlock::~GameSaveBlock()
{
	delete trainer;
	delete inv;
}


void GameSaveBlock::update()
{

	std::copy(bytes + 0xA000, bytes + 0xB000, trainer->bytes);

	std::copy(bytes + 0xB000, bytes + 0xC000, inv->bytes);
}