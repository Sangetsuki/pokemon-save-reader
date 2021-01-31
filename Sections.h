#include "defines.h"

class GameSaveBlock; // acess another section from section

class Section
{
public:
	Section(char* data, uint16_t id, uint16_t checksum, uint32_t index, GameSaveBlock* SaveBlock);
	
	uint16_t id;
	uint16_t checksum;
	uint32_t index;
private:
	char data[SectionSize];
	GameSaveBlock* SaveBlock;
};

class TrainerInfo : public Section
{
public:
	static const uint16_t id = 0;

	TrainerInfo(char* data, uint16_t id, uint16_t checksum, uint32_t index, GameSaveBlock* SaveBlock);

	char name[8];
	uint8_t gender;
	uint16_t TID;
	uint16_t SID;
	uint32_t game;
	uint32_t secret;
};