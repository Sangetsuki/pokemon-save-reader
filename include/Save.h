#include "defines.h"
#include <fstream>

class GameSaveBlock;

class Save
{
public:
	Save(const char* path);
	~Save();

	GameSaveBlock* SaveBlock;

	void saveFile();
private:
	u16 getSaveBlockOffset();
	char bytes[TotalSize];
	std::ofstream file;
};