
#include "app.h"
#include "interrupt.h"
#include "calculator.h"
#include "log.h"
#include "rf_func.h"
#include "board.h"

Int_FlagInType State = {.au32Value = 0};
Int_FlagInType MaskState = {.au32Value = 0};

UARTDataType Lora_Rec;
UARTDataType DBG_Rec;

uint8_t Lora_u8Seq;

bool Flag_Broken = false;
bool Flag_BilletJamp = false;

void RS485_SendBuffer(uint8_t* buf, uint16_t len)
{
    HAL_GPIO_WritePin(RS485_ENB_GPIO_Port, RS485_ENB_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
    HAL_UART_Transmit(&huart3, buf, len, len + 10);
    HAL_Delay(4);
    HAL_GPIO_WritePin(RS485_ENB_GPIO_Port, RS485_ENB_Pin, GPIO_PIN_SET);
}

void RS485_SendStr(char* str)
{
    HAL_GPIO_WritePin(RS485_ENB_GPIO_Port, RS485_ENB_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
    HAL_UART_Transmit(&huart3, (uint8_t*)str, strlen(str), strlen(str) + 10);
    HAL_Delay(4);
    HAL_GPIO_WritePin(RS485_ENB_GPIO_Port, RS485_ENB_Pin, GPIO_PIN_SET);
}

void Lora_Send(uint8_t *buf, uint16_t len)
{
#ifdef DBG_SEND
    DBG_SendStr("Lora_Send\n");
	DBG_SendBuffer(buf, len);
#endif
	HAL_UART_Transmit(&huart1, buf, len, len<<1);
}


void Beacon_ResponseProcess(void)
{
    if (true == State.bits.S_PROCESS_BEACON)
    {
        if (Beacon.u32TimeWait <= (HAL_GetTick() - Beacon.u32TimeOut))
        {
			uint8_t buf[12] = {STX, 0, 0, CMD_BEACON };
			uint8_t buf_len = 0;

			buf_len = 9;
			buf[1] = buf_len;
			buf[2] = Lora_u8Seq++;

			buf[4] = Address.u8Full;
			//buf[5] = Battery_Measurement();
			//buf[6] = GetAllInput();
			buf[buf_len - 1] = ETX;
			buf[buf_len - 2] = XOR_Cal(buf, 1, buf_len - 3);
		#ifdef DBG_SEND
			DBG_SendStr("Beacon_RespondProcess\n");
			DBG_SendBuffer(buf, buf_len);
		#endif
			Lora_Send(buf, buf_len);
            State.bits.S_PROCESS_BEACON = false;
        }
    }
}

void Lora_Process(void)
{
    uint8_t buf[20];
    uint8_t buf_len = 0;

    if (true == State.bits.S_PROCESS_LORA)
    {
#ifdef DBG_SEND
        DBG_SendStr("Lora_Process\n");
        DBG_SendBuffer(Lora_Rec.au8Buf, Lora_Rec.u8Len);
#endif
        buf_len = Lora_Rec.u8Len;
        memcpy(buf, Lora_Rec.au8Buf, buf_len);
        memset(&Lora_Rec, 0, sizeof(Lora_Rec));
        if ((buf_len == buf[1]) && (true == XOR_Check(buf, 1, buf_len - 3, buf[buf_len - 2])) &&
            (SOH == buf[0]) && (ETX == buf[buf_len - 1]) && (Address.u8Master == (buf[4] & ADDR_MASTER)))
        {
#ifdef DBG_SEND
            DBG_SendStr("Lora_Process\n");
#endif
            switch(buf[3]) //cmd
            {
            case CMD_BEACON:
#ifdef DBG_SEND
                DBG_SendStr("CMD_BEACON\n");
#endif
                Beacon.u32TimeOut = HAL_GetTick();
                State.bits.S_PROCESS_BEACON = true;
                break;
            }
        }
        State.bits.S_PROCESS_LORA = false;
    }
}


void LoadBattery(void)
{
//    char buf1[13] = "Start RS485\n";
//    char buf2[13] = "Start RS232\n";
//    char buf3[13] = "Start Debug\n";
    State.bits.S_STARTUP = true;
    for (uint8_t i = 0; i < 6; i++)
    {
        HAL_GPIO_TogglePin(LED_RUN_GPIO_Port, LED_RUN_Pin);
        HAL_Delay(100);
        WDT_Clear();
    }
	SetupInit();
#ifdef DBG_SEND
    logLen = sprintf(log1, "Address.eu8Mode = %d\n", (uint16_t)Address.eu8Mode);
    DBG_SendStr(log1);
    logLen = sprintf(log1, "Address.u8Master = %d\n", (uint16_t)Address.u8Master);
    DBG_SendStr(log1);
    DBG_SendBuffer(&Address.u8Master, 1);
    logLen = sprintf(log1, "Address.u8Slave = %d\n", (uint16_t)Address.u8Slave);
    DBG_SendStr(log1);
    DBG_SendBuffer(&Address.u8Slave, 1);
    logLen = sprintf(log1, "Address.u8Full = %d\n", (uint16_t)Address.u8Full);
    DBG_SendStr(log1);
    DBG_SendBuffer(&Address.u8Full, 1);
    logLen = sprintf(log1, "Beacon.u32TimeWait = %d\n", Beacon.u32TimeWait);
    DBG_SendStr(log1);
    logLen = sprintf(log1, "Address.eu8NumInput = %d\n", Address.eu8NumInput);
    DBG_SendStr(log1);
	//Battery_Measurement();
	//DebugOut();
#endif
    State.bits.S_STARTUP = false;
}

static bool AnalyzeRfRec(uint8_t *buf, uint8_t len)
{
#ifdef DBG_SEND
	DBG_SendStr("AnalyzeRfRec\n");
	DBG_SendBuffer(buf, len);
#endif
	if ((len == buf[1]) && (true == XOR_Check(buf, 1, len - 3, buf[len - 2])) &&
	(STX == buf[0]) && (ETX == buf[len - 1]) && (Address.u8Master == (buf[4] & ADDR_MASTER)))
	{
#ifdef DBG_SEND
		DBG_SendStr("AnalyzeRfRec\n");
#endif
		return true;
	}
	return false;
}

void Rf_RecProcess(void)
{
	if (true == Rf.bFlagRec)
	{
#ifdef DBG_SEND
        DBG_SendStr("Rf_RecProcess\n");
#endif
		Rf_ReceiveData(Rf.au8Buf, &Rf.u16BufRealLen);
		Rf_OldDataLen = Rf.u16BufRealLen;
		memcpy(Rf_OldData, Rf.au8Buf, Rf_OldDataLen);
		if (true == AnalyzeRfRec(Rf_OldData, Rf_OldDataLen))
		{
#ifdef DBG_SEND
			logLen = sprintf(log1, "INPUT=%d\n",Rf.au8Buf[5]>>4);
        	DBG_SendStr(log1);
#endif
			Rf.au8Buf[2] = Lora_u8Seq++;
			Rf.au8Buf[Rf.u16BufRealLen - 2] = XOR_Cal(Rf.au8Buf, 1, Rf.u16BufRealLen - 3);
			Lora_Send(Rf.au8Buf, Rf.u16BufRealLen);
		}
		Rf_SendData((uint8_t*)"V1 TRANSFER RETURN\n", 19);
		Rf_ModeRx();
		Rf.bFlagRec = false;
		u32TimeConfigRf = 0;
	}
}

void Rf_Config(void)
{
	 if (20000 <=u32TimeConfigRf)
	 {
		 //Battery_Measurement();
		 Rf_Init();
		 Rf_ModeRx();
		 u32TimeConfigRf = 0;
	 }
}