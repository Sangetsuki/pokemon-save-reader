#include "defines.h"

template <typename T> // Section<TrainerInfo> = section 0 (player data)
class Section
{
public:
	T* data;
	u16 id;
	u16 checksum;
	u32 index;

	Section(char* data, u16 id, u16 checksum, u32 index)
	{
		this->id = id;
		this->checksum = checksum;
		this->index = index;
		this->data = new T(data);
	};

	~Section()
	{
		delete data;
	}

	u16 updateChecksum()
	{
		// DO CHECKSUM CALCULATION
		return checksum;
	}
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
private:
	char PokeToAscii(u8 target);
};