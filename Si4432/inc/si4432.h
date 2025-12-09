
#ifndef __SI4432_H
#define __SI4432_H
#include "main.h"
#include <stdbool.h>
extern uint8_t Si4432_IntStatus1;
extern uint8_t Si4432_IntStatus2;
extern bool nIRQ_Enable;

void Si4432_WriteReg(uint8_t reg, uint8_t val);

uint8_t Si4432_ReadReg(uint8_t reg);

void Si4432_ClearFlag(void);

void Si4432_SetChannel(const uint8_t channel);

void Si4432_ModeTx(void);

void Si4432_ModeRx(void);

void Si4432_ModeStandBy(void);

void Si4432_SendRf(uint8_t* buf, const uint8_t len);

uint8_t Si4432_ReceiveData(uint8_t* buf, uint8_t* len);

void Si4432_Init(void);

#endif
