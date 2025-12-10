
#include "interrupt.h"
#include "board.h"
#include "si4432.h"
#include "rf_func.h"
#include "log.h"
#include "inc_def.h"

#define TIME_WAIT_SEND_LORA (uint16_t)(50)

volatile uint16_t LED_Blink = 0;
volatile uint16_t u16TimeWaitSendLora = 0;
volatile uint32_t u32TimeSendVol = 0;

volatile uint32_t u32TimeConfigRf;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7))
	{
		if (true == nIRQ_Enable)
		{
			Si4432_ClearFlag();
			if ((Si4432_IntStatus2 & 0x80) == 0x80)
			{
				Rf.u8RssiSignal = Si4432_ReadReg(0x26);
			}
			if ((Si4432_IntStatus1 & 0x02) == 0x02)
			{
				Rf.bFlagRec = true;
			}
		}
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	if (htim->Instance == htim2.Instance)
	{
#ifdef DBG_SEND
        logTime++;
#endif
		u32TimeConfigRf++;
        if (false == State.bits.S_STARTUP)
        {
            if (900 <= (LED_Blink++))
            {
                HAL_GPIO_WritePin(LED_RUN_GPIO_Port, LED_STT_Pin, GPIO_PIN_RESET);
			}
            if (1000 <= LED_Blink)
            {
                HAL_GPIO_WritePin(LED_RUN_GPIO_Port, LED_STT_Pin, GPIO_PIN_SET);
                LED_Blink = 0;
            }
		}
	}
	else if (htim->Instance == htim3.Instance) // button, 10ms
	{

	}
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
    if (huart->Instance == USART1) //RS485
	{
		uint8_t rec1 = recUART1;
		HAL_UART_Receive_IT(&huart1, &recUART1, 1);
	}
    else if (huart->Instance == USART3) //DBG
	{
		uint8_t rec3 = recUART3;
		HAL_UART_Receive_IT(&huart3, &recUART3, 1);
	}
}


