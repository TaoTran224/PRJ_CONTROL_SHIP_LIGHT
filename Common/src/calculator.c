
#include "calculator.h"
#include "inc_def.h"
#include "string.h"
#include <stdbool.h>
/*
bool CompareBuffer(uint8_t* array1, uint16_t offset1, uint8_t* array2, uint16_t offset2, uint16_t len)
{
    uint16_t i, k = 0;
    for (i = 0; i < len; i++)
    {
        if (array1[offset1 + i] == array2[offset2 + i]) k++;
    }
    if (k == len) return true;
    else return false;
}

void ClearBuffer(uint8_t* input, uint16_t len)
{
    uint16_t i;
    for (i = 0; i < len; i++) { input[i] = 0x00; }
}
*/

void SwapByte(uint8_t* dst, uint8_t* src, uint8_t len)
{
	uint8_t i = 0;
	for (i = 0; i < len; i++)
	{
		dst[i] = src[len - 1 - i];
	}
}


uint8_t XOR_Cal(const uint8_t* buf, const uint16_t offset, const uint16_t len)
{
    uint8_t crc = 0;
    uint16_t i = 0;
    for (i = 0; i < len; i++)
    {
        crc ^= buf[i + offset];
    }
    return crc;
}

bool XOR_Check(const uint8_t* buf, const uint16_t offset, const uint16_t len, const uint8_t byteCheck)
{
    if (XOR_Cal(buf, offset, len) == byteCheck)
    {
        return true;
    }
    return false;
}

uint8_t SUM_Cal(const uint8_t* buf, const uint16_t offset, const uint16_t len)
{
    uint8_t crc = 0;
    uint16_t i = 0;
    for (i = 0; i < len; i++)
    {
        crc += buf[i + offset];
    }
    return crc;
}

bool SUM_Check(const uint8_t* buf, const uint16_t offset, const uint16_t len, const uint8_t byteCheck)
{
    if (SUM_Cal(buf, offset, len) == byteCheck)
    {
        return true;
    }
    return false;
}