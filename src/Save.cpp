#include "GameSaveBlock.h"
#include "Save.h"
#include "Binary.h"

Save::Save(const char* path)
{
	std::ifstream data(path, std::ios::in | std::ios::binary);
	data.read(bytes, TotalSize);
	data.close();
	file.open(path, std::ios::out | std::ios::binary);

	char gameblockdata[GameSaveASize];

	std::copy(bytes + getSaveBlockOffset(), bytes + getSaveBlockOffset() + GameSaveASize, gameblockdata);

	SaveBlock = new GameSaveBlock(gameblockdata);
}

Save::~Save()
{
	saveFile();
	file.close();
	delete SaveBlock;
}

u16 Save::getSaveBlockOffset()
{
	u32 SaveBlockAIndex = getBytes<u32>(bytes, 0x0FFC);
	u32 SaveBlockBIndex = getBytes<u32>(bytes, GameSaveASize + 0x0FFC);

	return SaveBlockAIndex > SaveBlockBIndex ? 0x0000 : GameSaveASize;
}

void Save::saveFile()
{
	SaveBlock->update();
	std::copy(SaveBlock->bytes, SaveBlock->bytes + GameSaveASize, bytes + getSaveBlockOffset());
	file.write(bytes, TotalSize);
}
