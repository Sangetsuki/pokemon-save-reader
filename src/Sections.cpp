#include "GameSaveBlock.h"
#include "Sections.h"
#include "Binary.h"
#include <iostream>

template <typename T>
Section<T>::Section(char* data, u16 id, u16 checksum, u32 index) : T(data)
{
	this->id = id;
	this->checksum = checksum;
	this->index = index;
};

TrainerInfo::TrainerInfo(char* data)
{
	for (u8 i = 0; i < 8; i++)
	{
		name[i] = getByte(data, 0x0000 + i); // needs to be converted to ascii
	}
	
	gender = getByte(data, 0x0008);
	TID = getBytes<u16>(data, 0x000A);
	SID = getBytes<u16>(data, 0x000C);
	secret = getBytes<u32>(data, 0x00AC);
}