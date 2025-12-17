
#include "log.h"
#include "usart.h"
#include <string.h>

char log1[LOG_MAX_SIZE];
uint8_t logLen;
uint16_t logTime;
void DBG_SendStr(const char* str)
{
	HAL_UART_Transmit(&huart3, (uint8_t*)str, strlen(str), strlen(str));

	HAL_GPIO_WritePin(RS485_ENB_GPIO_Port, RS485_ENB_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), strlen(str) + 10);
    HAL_Delay(2);
    HAL_GPIO_WritePin(RS485_ENB_GPIO_Port, RS485_ENB_Pin, GPIO_PIN_RESET);

}

void DBG_SendBuffer(uint8_t *buf, const uint16_t len)
{
    HAL_UART_Transmit(&huart3, buf, len, len);

    HAL_GPIO_WritePin(RS485_ENB_GPIO_Port, RS485_ENB_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_UART_Transmit(&huart1, buf, len, len + 10);
    HAL_Delay(2);
    HAL_GPIO_WritePin(RS485_ENB_GPIO_Port, RS485_ENB_Pin, GPIO_PIN_RESET);
}

