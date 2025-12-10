

#include <board.h>
#include "main.h"
#include "iwdg.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "spi.h"
#include "log.h"

BeaconType Beacon;


uint8_t recUART1;
uint8_t recUART3;

AddressType Address;

uint16_t Detect_u16Timeout = 0;


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}



void SetupInit(void)
{

    Address.u8Full = ((uint8_t)((~HAL_GPIO_ReadPin(S1_GPIO_Port, S1_Pin)) & 0x01) << 2) | \
		              ((uint8_t)((~HAL_GPIO_ReadPin(S2_GPIO_Port, S2_Pin)) & 0x01) << 1) | \
                       (uint8_t)((~HAL_GPIO_ReadPin(S3_GPIO_Port, S3_Pin)) & 0x01);
	Address.u8Master = Address.u8Full;
    Address.u8Slave = Address.u8Full;
//    Beacon.u32TimeWait = (((uint32_t)Address.u8Slave) << 9) + 200;
//    Beacon.u8TimeWaitToSendLora = Address.u8Slave << 4;
}

void StartUp(void)
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_IWDG_Init();
  MX_SPI2_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
    /* USER CODE BEGIN 2 */

    /* USER CODE END 2 */

    HAL_UART_Receive_IT(&huart1, &recUART1, 1);
    //HAL_UART_Receive_IT(&huart2, &recUART2, 1);
	HAL_UART_Receive_IT(&huart3, &recUART3, 1);
    /* USER CODE BEGIN 2 */
    HAL_TIM_Base_Start_IT(&htim2);
    HAL_TIM_Base_Start_IT(&htim3);
    //HAL_TIM_Base_Start_IT(&htim4);
    /* USER CODE END 2 */
}

void delay_us(uint32_t t)
{
    uint32_t i = 0;
    for ( i = 0; i < (6 * t); i++)
    {
        ;;

    }

}

void delay_ms(uint32_t t)
{
    uint32_t i = 0;
    for ( i = 0; i < (6600 * t); i++)
    {
        ;;

    }

}


void WDT_Clear(void)
{
	HAL_IWDG_Refresh(&hiwdg);
}


