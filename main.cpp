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

	char name[8];
	save.getPlayerName(name);

	std::cout << "Seu nome é: " << name << std::endl;
	if (!save.getPlayerGender())
	{
		std::cout << "Voce é um garoto" << std::endl;
	} else {
		std::cout << "Voce é uma garota" << std::endl;
	}
	std::cout << "Seu TID é: " << save.getPlayerID() << std::endl;
	std::cout << "Seu dinheiro é: " << save.getPlayerMoney() << std::endl;

	return 0;
}