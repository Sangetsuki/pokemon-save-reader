#include "defines.h"

class Section;
class Save;
class TrainerInfo;

class GameSaveBlock
{
public:
	GameSaveBlock(char* data, Save* save);
	~GameSaveBlock();

	Section* getSection(uint16_t id); // T will change according to section

	Save* saveFile;
private:
	Section* sections[NumOfSections];
};