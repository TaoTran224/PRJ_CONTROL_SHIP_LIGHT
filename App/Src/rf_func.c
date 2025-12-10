
#include "rf_func.h"
#include "si4432.h"
#include "log.h"
#include "board.h"
uint8_t Rf_OldData[RF_OLD_MAX_SIZE];
uint8_t Rf_OldDataLen;

RfType Rf;
void Rf_Init(void)
{
    Si4432_Init();
	Rf_SetChannel(Address.u8Full);
}

void Rf_SendData(uint8_t* buf, const uint8_t len)
{
    Si4432_SendRf(buf, len);
}

void Rf_Send3Time(uint8_t* buf, const uint8_t len, const uint8_t delay_time)
{
    uint8_t i = 0;
#ifdef DBG_SEND
    DBG_SendBuffer(buf, (uint16_t)len);
#endif
    for (i = 0; i < 3; i++)
    {
        Rf_SendData(buf, len);
        if (2 > i)
        {
            HAL_Delay(delay_time);
        }
    }
}

uint8_t Rf_ReceiveData(uint8_t* buf, uint8_t* len)
{
     return Si4432_ReceiveData(buf, len);
}

void Rf_SetChannel(const uint8_t channel)
{
    Si4432_SetChannel(channel);
}

void Rf_ModeRx(void)
{
    Si4432_ModeRx();
}

void Rf_ModeStandBy(void)
{
    Si4432_ModeStandBy();
}
