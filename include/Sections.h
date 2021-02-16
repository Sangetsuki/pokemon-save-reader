#include "defines.h"
#include "Binary.h"

class Section
{
public:
	u16 id;
	u16 checksum;
	u32 index;

	Section(char* data)
	{
		id = getBytes<u16>(data, 0x0FF4);
		checksum = getBytes<u16>(data, 0x0FF6);
		index = getBytes<u32>(data, 0x0FFC);
	};

	~Section()
	{
	}

	u16 updateChecksum()
	{
		// DO CHECKSUM CALCULATION
		return checksum;
	}
};

class TrainerInfo : public Section
{
public:
	TrainerInfo(char* data);

	char name[8];
	u8 gender;
	u16 TID;
	u16 SID;
	// u32 game;
	u32 secret;
};

class TrainerInventory : public Section
{
public:
	TrainerInventory(char* data);

	u32 partySize;
	u32 money;
};