#include "Binary.h"

u8 getByte(char* data, u16 offset)
{
	u32 unsigData = (u32)data[offset] & 0xFF;
	return (u8)unsigData;
};

u8 setByte(char* data, u16 offset, u8 newByte)
{
	data[offset] = newByte;
	return getByte(data, offset);
};
