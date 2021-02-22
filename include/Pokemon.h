#include "defines.h"

enum stats
{
	HP = 0,
	Attack,
	Defense,
	Speed,
	SpAttack,
	SpDefense
};

enum contestStats
{
	Cool = 0,
	Beauty,
	Cute,
	Smart,
	Tough
};


class PokemonGrowth
{
public:
	PokemonGrowth(char* data);

	u16 species;
	u16 item;
	u32 xp;
	u8 PP;
	u8 friendship;
};

class PokemonAttacks
{
public:
	PokemonAttacks(char* data);

	u16 moves[4];
	u8 pp[4];
};

class PokemonCondition
{
public:
	PokemonCondition(char* data);

	u8 EV[6];
	u8 contest[5];
	u8 Feel;
};

class PokemonMisc
{
public:
	PokemonMisc(char* data);

	u8 pokerus;
	u8 met;
	u16 origin;
	u8 IV[6];
	bool egg;
	u8 ability;
};

class Pokemon
{
public:
	Pokemon(char* data);

	u32 PID;
	u32 TID;

	char Nickname[10];
	u16 Language;
	char Tname[8];
	u8 markings;
	u16 Checksum;

 	u16 unknown;

	PokemonGrowth growth;
	PokemonAttacks attacks;
	PokemonCondition condition;
	PokemonMisc misc;

	u32 Status;

	u8 Level;

	u8 Pokerus;

	u16 CurrentHP;
	u16 stats[6]; // index = stats enum
};

u16 getGrowthOffset(u32 PID);
u16 getAttacksOffset(u32 PID);
u16 getConditionOffset(u32 PID);
u16 getMiscOffset(u32 PID);

void decrypt(char* data, u32 PID, u32 TID);