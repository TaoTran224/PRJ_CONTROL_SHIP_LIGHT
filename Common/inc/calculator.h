
#ifndef _CACULATOR_H
#define _CACULATOR_H
#include "main.h"
#include "stdbool.h"

//bool CompareBuffer(uint8_t* array1, uint16_t offset1, uint8_t* array2, uint16_t offset2, uint16_t len);

//void ClearBuffer(uint8_t* input, uint16_t len);

void SwapByte(uint8_t* dst, uint8_t* src, uint8_t len);

uint8_t XOR_Cal(const uint8_t* buf, const uint16_t offset, const uint16_t len);

bool XOR_Check(const uint8_t* buf, const uint16_t offset, const uint16_t len, const uint8_t byteCheck);

uint8_t SUM_Cal(const uint8_t* buf, const uint16_t offset, const uint16_t len);

bool SUM_Check(const uint8_t* buf, const uint16_t offset, const uint16_t len, const uint8_t byteCheck);
void ConvertBcdToHex(uint8_t*dst, const uint8_t *src);

//uint8_t NumCharToByte(const uint8_t* c);

//bool NumStringToByteArray(uint8_t* arr, const uint8_t* str, const uint8_t length);

#endif