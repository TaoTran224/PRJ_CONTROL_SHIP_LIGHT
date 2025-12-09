
#ifndef __RF_FUNC_H
#define __RF_FUNC_H
#include "main.h"
#include <stdbool.h>
#define RF_CH_8 (uint8_t)8

#define RF_MAX_SIZE (uint16_t)64
#define RF_OLD_MAX_SIZE (uint8_t)64

extern uint8_t Rf_OldData[RF_OLD_MAX_SIZE];
extern uint8_t Rf_OldDataLen;

typedef enum {
RF_SEARCH = 0,
//RF_18E,
//RF_17E,
RF_PROG_NUM,
RF_LAST_PROG_TIME,
//RF_MB_E,
//RF_MB_MD,
RF_NORMAL_OBIS,
RF_ACK,
RF_FINISH,
RF_CLOSE,
} Rf_CmdType;

typedef struct {
  				  //uint16_t u16BufAllLen;
                  uint8_t u16BufRealLen;
                  //Rf_CmdType eu8Cmd;
                  uint8_t au8Buf[RF_MAX_SIZE];
                  uint8_t u8RssiSignal;
				  //uint8_t u8Seq;
				  bool bFlagRec;
				  //uint8_t u8ScanTimes;
               }  RfType;

extern RfType Rf;


extern bool flagOfRF_RetrySend;
extern uint8_t countOfRF_RetrySend;

void Rf_Init(void);

void Rf_SendData(uint8_t* buf, const uint8_t len);

void Rf_Send3Time(uint8_t* buf, const uint8_t len, const uint8_t delay_time);

uint8_t Rf_ReceiveData(uint8_t* buf, uint8_t* len);

void Rf_SetChannel(const uint8_t channel);

void Rf_ModeRx(void);

void Rf_ModeStandBy(void);

#endif

