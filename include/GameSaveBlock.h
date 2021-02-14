#include "defines.h"
#include "Sections.h"

class GameSaveBlock
{
public:
	GameSaveBlock(char* data);
	~GameSaveBlock();

	Section<TrainerInfo>* trainerData; // somehow i'll have to put this in an array

	/*template <typename T>
	Section<T>* getSection(); // id % 14, T for dynamic section. NOT GOOD :(

private:
	BaseSection* sections[NumOfSections];*/
};