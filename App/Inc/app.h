
#ifndef _APP_H_
#define _APP_H_

#include "main.h"
#include "board.h"


#define UART_MAX_LEN (uint16_t)(100)

#define SOH (uint8_t)0x01
#define STX (uint8_t)0x02
#define ETX (uint8_t)0x03

typedef struct
{
    uint8_t S_STARTUP : 1;
	uint8_t S_PROCESS_BUTTON : 1;
    uint8_t S_PROCESS_LORA : 1;
//    uint8_t S_WAIT_LORA : 1;
    uint8_t S_SEND_DBG : 1;
    uint8_t S_SEND_SHORT_CUT_ERROR : 1;
    uint8_t S_SEND_FINISH_SHORT_CUT_ERROR : 1;
	uint8_t S_SEND_BROKEN : 1;
    uint8_t S_SEND_FINISH_BROKEN : 1;
	uint8_t S_CTRL_OUTPUT : 1;
    uint8_t S_PROCESS_BEACON : 1;
	uint8_t S_CONFIG_RF : 1;
} BITS;

typedef union
{
    BITS bits;
    uint32_t au32Value;
} Int_FlagInType;

extern Int_FlagInType State;
extern Int_FlagInType MaskState;

typedef struct
{
    uint8_t au8Buf[UART_MAX_LEN];
    uint8_t u8Len;
    uint16_t u16Timeout;
    bool bFlagRec;
} __attribute__((packed)) UARTDataType;

extern UARTDataType Lora_Rec;
extern UARTDataType DBG_Rec;

extern uint8_t Lora_u8Seq;

extern bool Flag_Broken;
extern bool Flag_BilletJamp;

void RS485_SendBuffer(uint8_t* buf, uint16_t len);
void RS485_SendStr(char* str);

void Lora_Send(uint8_t *buf, uint16_t len);

void DBG_Process(void);

void Beacon_ResponseProcess(void);
void Lora_Process(void);

void Rf_RecProcess(void);
void Rf_Config(void);

void Config_Module(void);


void DebugInOut(void);

void DebugOut(void);

void Led_Display(void);
void Output_Process(void);

#endif
