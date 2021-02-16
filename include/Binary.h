#include "defines.h"
#include <iostream>

u8 getByte(char* data, u16 offset);
u8 setByte(char* data, u16 offset, u8 newByte);

template <typename T>
T getBytes(char* data, u16 offset)
{
	T result = 0;
	for (u16 i = 0; i < sizeof(T); i++)
	{
		result |= (getByte(data, offset + i)) << (8 * i);
	}
	return result;
}

template <typename T>
T setBytes(char* data, u16 offset, T newBytes)
{
	for (T i = 0; i < sizeof(T); i++)
	{
		data[offset + i] = (newBytes >> (8 * i)) & 0xFF;
	}
	return getBytes<T>(data, offset);
}