#include "defines.h"
#include "Binary.h"

class Pokemon;

class Section
{
public:
	Section(char* data);
	u32 checksum;

	u32 updateChecksum(); // auto calculates valid checksum and sets it to checksum
protected:
	friend class GameSaveBlock;
	u32 id, index; // you really don't want to change them manually 
	char bytes[SectionSize]; // needed to save file
};

class TrainerInfo : public Section
{
public:
	TrainerInfo(char* data);

	// these need to be getters and setters (so changes can also change internal bytes)
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
	~TrainerInventory();

	u32 getpartySize();

	u32 getMoney(); // must be XORed with secret to yield true value
	u32 setMoney(u32 money);

	Pokemon* party[6];
};