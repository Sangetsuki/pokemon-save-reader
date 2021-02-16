#include "defines.h"
#include <vector>

class Section;
class TrainerInfo;
class TrainerInventory;
class Save;

class GameSaveBlock
{
public:
	GameSaveBlock(char* data);
	~GameSaveBlock();

	void update();

	TrainerInfo* trainer;
	TrainerInventory* inv;
private:
	friend class Save;
	char bytes[GameSaveASize];
};