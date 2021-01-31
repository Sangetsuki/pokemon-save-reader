#include "GameSaveBlock.h"
#include "Sections.h"
#include "Save.h"
#include <iostream>

Section::Section(char* data, uint16_t id, uint16_t checksum, uint32_t index, GameSaveBlock* SaveBlock)
{
	memcpy(this->data, data, SectionSize);
	this->id = id;
	this->checksum = checksum;
	this->index = index;
	this->SaveBlock = SaveBlock;
};

TrainerInfo::TrainerInfo(char* data, uint16_t id, uint16_t checksum, uint32_t index, GameSaveBlock* SaveBlock): Section(data, id, checksum, index, SaveBlock)
{
	gender = (uint32_t)data[0x0008] & 0xFF;
}