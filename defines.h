#include <cstring>
#include <cstdint>

#define GameSaveASize 0xE000
#define GameSaveBSize 0xE000
#define HallOfFameSize 0x2000
#define MisteryGiftSize 0x1000
#define RecordedBattleSize 0x1000
#define TotalSize GameSaveASize + GameSaveBSize + HallOfFameSize + MisteryGiftSize + RecordedBattleSize

#define SectionSize 0x1000
#define NumOfSections 14

#define Sectionsize0 0x0F2C
#define Sectionsize1 0x0F80
#define Sectionsize2 0x0F80
#define Sectionsize3 0x0F80
#define Sectionsize4 0x0F08
#define Sectionsize5 0x0F80
#define Sectionsize6 0x0F80
#define Sectionsize7 0x0F80
#define Sectionsize8 0x0F80
#define Sectionsize9 0x0F80
#define Sectionsize10 0x0F80
#define Sectionsize11 0x0F80
#define Sectionsize12 0x0F80
#define Sectionsize13 0x07D0