#include "defines.h"
#include <fstream>

class GameSaveBlock;

class Save
{
public:
	Save(const char* path);
	~Save();

	uint16_t getSaveBlockOffset(); // current block

	uint16_t getSection(uint8_t id); // from current block

	uint32_t getByte(uint16_t offset);
	uint32_t getBytes(uint16_t offset, uint16_t size);

	uint32_t setByte(uint16_t offset, uint32_t newByte);
	uint32_t setBytes(uint16_t offset, uint32_t newBytes, uint16_t size);

	void saveFile();

	GameSaveBlock* SaveBlock;


private:
	char bytes[TotalSize];
	std::ofstream file;
};