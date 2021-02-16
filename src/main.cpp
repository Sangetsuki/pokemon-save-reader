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

	char* name = save.SaveBlock->trainer->name;
	u32 secret = save.SaveBlock->trainer->secret;
	u32 moneyXOR = save.SaveBlock->inv->getMoney();

	u32 money = secret ^ moneyXOR;

	std::cout << "Ola " << name << std::endl;
	std::cout << "Voce tem " << money << "$" << std::endl;
	std::cout << "Vou te dar 500$ para te ajudar!" << std::endl;

	money += 500;

	save.SaveBlock->inv->setMoney(secret ^ money);
	moneyXOR = save.SaveBlock->inv->getMoney();

	std::cout << "agora vc tem " << (secret ^ moneyXOR) << "$. Yey" << std::endl;

	std::cout << "sua checksum desatualizada é " << save.SaveBlock->inv->checksum << std::endl;
	std::cout << "ela foi atualizada para " << save.SaveBlock->inv->updateChecksum() << std::endl;

	return 0;
}