#include "defines.h"
#include <fstream>

class Save
{
public:
	Save(const char* path);
	~Save();

	uint16_t getSaveBlockOffset(); // current block

	uint16_t getSection(uint8_t id); // from current block

	/*uint16_t getChecksum(uint8_t section);
	uint16_t getChecksum(uint8_t section, uint8_t block);

	uint16_t genChecksum(uint8_t section);
	uint16_t genChecksum(uint8_t section, uint8_t block);*/

	char* getPlayerName(char* target);

	uint16_t getPlayerGender(); // FALSE/0 for boy, TRUE/1 for female
	uint16_t setPlayerGender(uint16_t newGender); // even for male, odd for female

	uint16_t getPlayerID();
	uint16_t getPlayerSID();
	
	uint32_t convertToAscii(uint32_t id);

	uint32_t getPlayerGame(); // 0 for RS, 1 for FRLG, 2 for EMERALD

	uint32_t getPlayerSecret();

	uint32_t getPlayerMoney();
	uint32_t setPlayerMoney(uint32_t amount);

	uint32_t getByte(uint16_t offset);
	uint32_t getBytes(uint16_t offset, uint16_t size);

	uint32_t setByte(uint16_t offset, uint32_t newByte);
	uint32_t setBytes(uint16_t offset, uint32_t newBytes, uint16_t size);

	void saveFile();


private:
	char bytes[TotalSize];
	std::ofstream file;
};