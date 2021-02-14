#include "Save.h"
#include "GameSaveBlock.h"
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

	std::cout << save.SaveBlock->trainerData->data->name << std::endl;

	return 0;
}