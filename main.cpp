#include "Save.h"
#include <iostream>

int main(int agrc, char* argv[])
{
	Save save("../pokeemerald/pokeemerald.sav");

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