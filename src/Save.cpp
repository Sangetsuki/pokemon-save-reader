#include "GameSaveBlock.h"
#include "Sections.h"
#include "Save.h"

Save::Save(const char* path)
{
	std::ifstream data(path, std::ios::in | std::ios::binary);
	data.read(bytes, TotalSize);
	data.close();
	file.open(path, std::ios::out | std::ios::binary);

	char gameblockdata[GameSaveASize];

	std::copy(data + getSaveBlockOffset(), data + getSaveBlockOffset() + GameSaveASize, gameblockdata)

	SaveBlock = new GameSaveBlock(gameblockdata);
}; 

Save::~Save()
{
	saveFile();
	file.close();
	delete SaveBlock;
};

uint16_t Save::getSaveBlockOffset()
{
	u32 SaveBlockAIndex = getBytes<u32>(0x0FFC);
	u32 SaveBlockBIndex = getByte(GameSaveASize + 0x0FFC);

	return SaveBlockAIndex > SaveBlockBIndex ? 0x0000 : GameSaveASize;
};

void Save::saveFile()
{
	file.write(bytes, TotalSize);
};
