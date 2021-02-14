#include "defines.h"
#include <fstream>

class GameSaveBlock;

class Save
{
public:
	Save(const char* path);
	~Save();

	uint16_t getSaveBlockOffset(); // current block

	void saveFile();

	GameSaveBlock* SaveBlock;
private:
	char bytes[TotalSize];
	std::ofstream file;
};