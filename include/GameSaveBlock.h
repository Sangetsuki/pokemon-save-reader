#include "defines.h"
#include "Sections.h"

class GameSaveBlock
{
public:
	GameSaveBlock(char* data);
	~GameSaveBlock();

	Section<TrainerInfo>* trainerData;

	/*template <typename T>
	Section<T>* getSection(); // id % 14, T for dynamic section. NOT GOOD :(

private:
	BaseSection* sections[NumOfSections];*/
};