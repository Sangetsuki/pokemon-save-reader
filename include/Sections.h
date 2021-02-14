#include "defines.h"

template <typename T> // Section<TrainerInfo> = section 1 (player data)
class Section
{
public:
	Section(char* data, u16 id, u16 checksum, u32 index);

	T* data;
	u16 id;
	u16 checksum;
	u32 index;
};

class TrainerInfo
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