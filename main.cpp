#include "GameSaveBlock.h"
#include "Sections.h"
#include "Save.h"
#include <iostream>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Qual save quer abrir??" << std::endl;
		return -1;
	}

	Save save(argv[1]);

	Section* ti = save.SaveBlock->getSection(0);

	std::cout << ti->id << std::endl;

	return 0;
}