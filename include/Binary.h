#include "defines.h"

u8 getByte(char* data, u16 offset);
u8 setByte(char* data, u16 offset, u8 newByte);

template <typename T>
T getBytes(char* data, u16 offset);

template <typename T>
u8 setBytes(char* data, u16 offset, u16 size, u8 newBytes);