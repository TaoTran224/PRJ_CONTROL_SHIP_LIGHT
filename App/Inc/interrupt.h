#ifndef _INTERRUP_H_
#define _INTERRUP_H_

#include "board.h"
#include "app.h"


#define BUTTON_TIMEOUT (uint32_t)(10)

extern volatile uint16_t u16TimeWaitSendLora;

extern volatile uint32_t u32TimeSendVol;

extern volatile uint32_t u32TimeConfigRf;
#endif