#include "defines.h"

class TrainerInfo;
class TrainerInventory;

class GameSaveBlock
{
public:
	GameSaveBlock(char* data);
	~GameSaveBlock();

	TrainerInfo* trainerData; // somehow i'll have to put this in an array
	TrainerInventory* inv;
 
	/*template <typename T>
	Section<T>* getSection(); // id % 14, T for dynamic section. NOT GOOD :(

private:
	BaseSection* sections[NumOfSections];*/
};