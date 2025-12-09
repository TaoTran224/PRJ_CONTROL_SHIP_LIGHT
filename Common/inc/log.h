

#ifndef __LOG_H
#define __LOG_H
#include "main.h"
#include "inc_def.h"
#include <string.h>
#include <stdio.h>
#define LOG_MAX_SIZE (uint8_t)120



#define DBG_SEND


extern char log1[LOG_MAX_SIZE];
extern uint8_t logLen;
extern uint16_t logTime;

void Log_SendByte(const uint8_t data);

void DBG_SendStr(const char* str);

void DBG_SendBuffer(uint8_t *buf, const uint16_t len);

#endif
