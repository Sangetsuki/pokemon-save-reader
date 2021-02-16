#include "Save.h"
#include "GameSaveBlock.h"
#include "Sections.h"
#include "defines.h"
#include <iostream>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Qual save quer abrir??" << std::endl;
		return -1;
	}

	Save save(argv[1]);

	u32 secret = save.SaveBlock->trainerData->secret;
	u32 moneyXOR = save.SaveBlock->inv->money;

	u32 money = secret ^ moneyXOR;

	std::cout << "secret: " << secret << std::endl;
	std::cout << "moneyXOR: " << moneyXOR << std::endl;
	std::cout << "money: " << money << std::endl;

	return 0;
}