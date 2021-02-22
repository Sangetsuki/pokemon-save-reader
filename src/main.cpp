#include "Save.h"
#include "GameSaveBlock.h"
#include "Sections.h"
#include "Pokemon.h"
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

	for (u8 i = 0; i < save.SaveBlock->inv->getpartySize(); i++)
	{
		Pokemon* pkmn = save.SaveBlock->inv->party[i];
		std::cout << "POkemon " << i + 1 << " se chama: " << pkmn->Nickname << std::endl;
		std::cout << "Capturado por: " << pkmn->Tname << std::endl;		
		std::cout << "chave: " << (pkmn->PID ^ pkmn->TID) << std::endl;
		std::cout << "Especie numero: " << (u32)pkmn->growth.species << std::endl;
		std::cout << "nivel: " << (u32)pkmn->Level << std::endl;
		std::cout << "hp maximo: " << (u32)pkmn->stats[HP] << std::endl;
		std::cout << "amizade: " << (u32)pkmn->growth.friendship << "/256" << std::endl;
		std::cout << (u32)pkmn->misc.ability<< std::endl;
		std::cout << (pkmn->misc.egg ? 1 : 0) << std::endl;
		std::cout << std::endl;
	}

	return 0;
}