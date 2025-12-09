

#include "si4432.h"
#include "spi.h"
#include "log.h"
#include "board.h"
#include "rf_func.h"
uint8_t Si4432_IntStatus1 = 0;
uint8_t Si4432_IntStatus2 = 0;


bool nIRQ_Enable = false;


//void Si4432_WriteReg(uint8_t reg, uint8_t val)
//{
//    uint8_t tx[2] = { reg | 0x80, val }; // Bit 7 = 1 d? ghi
//
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
//	delay_us(100);
//    HAL_SPI_Transmit(&hspi2, tx, 2, HAL_MAX_DELAY);
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
//}
//
//uint8_t Si4432_ReadReg(uint8_t reg)
//{
//    uint8_t tx = reg & 0x7F; // Bit 7 = 0 d? d?c
//    uint8_t rx;
//
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
//	delay_us(100);
//    HAL_SPI_Transmit(&hspi2, &tx, 1, HAL_MAX_DELAY);
//    HAL_SPI_Receive(&hspi2, &rx, 1, HAL_MAX_DELAY);
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
//
//    return rx; // byte th? 2 là d? li?u d?c
//}

 void Si4432_WriteReg(uint8_t reg, uint8_t val)
{
    uint8_t tx[2] = { reg | 0x80, val }; // Bit 7 = 1 d? ghi


    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	//delay_us(10);
    HAL_SPI_Transmit(&hspi2, tx, 2, 4); //HAL_MAX_DELAY
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	//delay_us(10);
}

uint8_t Si4432_ReadReg(uint8_t reg)
{
    uint8_t tx[2] = { 0x00, 0x00 }; // Bit 7 = 0 d? d?c   reg & 0x7F, 0x00 };
    uint8_t rx[2] = {0, 0};
	tx[0] = reg;
	tx[1] = reg;
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	//delay_us(10);
    HAL_SPI_TransmitReceive(&hspi2, tx, rx, 2, 4);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	//delay_us(10);
    return rx[1]; // byte th? 2 là d? li?u d?c
}

static void Si4432_PowerOn(void)
{
    HAL_GPIO_WritePin(SDN_GPIO_Port, SDN_Pin, GPIO_PIN_RESET);
}

static void Si4432_PowerOff(void)
{
	 HAL_GPIO_WritePin(SDN_GPIO_Port, SDN_Pin, GPIO_PIN_SET);
}

static void Si4432_InitHardware(void)
{

}

void IRQ_Pin_Disable(void)
{
	nIRQ_Enable = false;
}

void IRQ_Pin_Enable(void)
{
	nIRQ_Enable = true;
}

void Si4432_Reset(void)
{
	uint16_t timeout = 0xffff;
    Si4432_WriteReg(0x07, 0x80);
    while (GPIO_PIN_SET == HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)& ((--timeout) > 0));
    //read interrupt status registers to clear the interrupt flags and release nIRQ pin
}


void Si4432_ClearFlag(void)
{
    Si4432_IntStatus1 = Si4432_ReadReg(0x03); //read the Interrupt Status1 register
    Si4432_IntStatus2 = Si4432_ReadReg(0x04);
}

// 8 preamble + 4 header(0x00,0x00,0x00,0x00) + 4 sync + payload
static void Si4432_ConfigFreg(void)
{
    const uint8_t addr[56] = { 0x05, 0x06, 0x07, 0x09, 0x0A, 0x0B, 0x0C, 0x0E, 0x1C, 0x1D, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
                               0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x30, 0x32, 0x33, 0x34, 0x35, 0x3A, 0x3B, 0x3C, 0x3D, 0x3F, 0x40,
                               0x41, 0x42, 0x36, 0x37, 0x38, 0x39, 0x43, 0x44, 0x45, 0x46, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72,
                               0x73, 0x74, 0x75, 0x76, 0x77, 0x7A, 0x62, 0x69};
    const uint8_t val[56] = { 0x00, 0x00, 0x01, 0x52, 0x06, 0x12, 0x15, 0x00, 0x2D, 0x44, 0x32, 0x02, 0x8F, 0x5C, 0x07, 0xFF,
                              0x25, 0x00, 0x28, 0x3E, 0x29, 0x8D, 0xFF, 0x06, 0x08, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x64, 0x6E, 0x64, 0x6E, 0xFF, 0xFF, 0xFF, 0xFF, 0x1E, 0xA3, 0xD7, 0x20, 0x23, 0x10,
                              0x00, 0x00, 0x50, 0xFA, 0x00, 0x32, 0x24, 0x78};  // f = 410MHz, channel 500kHz
	//Cs thanh ghi 0x6D:0x1F max
    uint8_t i = 0;
#ifdef DBG_SEND
    DBG_SendStr("Si4432_ConfigFreg\n");
#endif

	Si4432_PowerOff();
    HAL_Delay(2);
    Si4432_PowerOn();
    HAL_Delay(30);
    Si4432_ClearFlag();

	for (i = 0; i < sizeof(addr); i++)
    {
        Si4432_WriteReg(addr[i], val[i]);
    }
}

void Si4432_SetChannel(const uint8_t channel)
{
    #ifdef DBG_SEND
	logLen = sprintf(log1, "Si4432_SetChannel=%d\n", channel);
	DBG_SendStr(log1);
    #endif
	Si4432_WriteReg(0x79, channel);
}

void Si4432_ModeTx(void)
{
    IRQ_Pin_Disable();
    Si4432_WriteReg(0x08, 0x03);// Tx and Rx FIFO Reset/Clear
    Si4432_WriteReg(0x08, 0x00);// RX FIFO Reset/Clear
    Si4432_WriteReg(0x05, 0x04); // Enable Packet Sent Int
}

void Si4432_ModeRx(void)
{
    IRQ_Pin_Enable();
    Si4432_WriteReg(0x08, 0x03);// Tx and Rx FIFO Reset/Clear
    Si4432_WriteReg(0x08, 0x00);// RX FIFO Reset/Clear
    Si4432_WriteReg(0x05, 0x02);//Enable Packet Rec Int
    Si4432_WriteReg(0x06, 0x80);
    Si4432_WriteReg(0x07, 0x05);// enter RX mode
}

void Si4432_ModeStandBy(void)
{
    IRQ_Pin_Disable();
    Si4432_WriteReg(0x07, 0x01);
}


void Si4432_SendRf(uint8_t* buf, const uint8_t len)
{
    uint16_t timeout = 0xffff;
    uint8_t i = 0;
	#ifdef DBG_SEND
    DBG_SendStr("Si4432_SendRf\n");
    DBG_SendBuffer(buf, len);
	#endif
    //LED_GREEN = LED_ON;
    Si4432_ModeTx();
    Si4432_WriteReg(0x3e, len);
    for (i = 0; i < len; i++)
    {
        Si4432_WriteReg(0x7f, buf[i]);
    }

    Si4432_ClearFlag();
    Si4432_WriteReg(0x07, 0x09);    //send
    while ((GPIO_PIN_SET == HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)) & ((--timeout) > 0)) ;
    Si4432_ClearFlag();
    //LED_GREEN = LED_OFF;
}

// tach lay mang du lieu RF nhan duoc
uint8_t Si4432_ReceiveData(uint8_t* buf, uint8_t* len)
{
    uint8_t i = 0;
	#ifdef DBG_SEND
	DBG_SendStr("Si4432_ReceiveData\n");
	#endif
    Si4432_ModeStandBy();
    //LED_RED = LED_ON;
    *len = Si4432_ReadReg(0x4b);
    Si4432_ClearFlag();
    for (i = 0; i < *len; i++)
    {
        buf[i] = Si4432_ReadReg(0x7f);
    }

    #ifdef DBG_SEND
	logLen = sprintf(log1, "Length=%d, RSSI = %d", *len, Rf.u8RssiSignal);
	DBG_SendStr(log1);
	DBG_SendBuffer(buf, *len);
    #endif
    //LED_RED = LED_OFF;
    return *len;
}

void Si4432_Init(void)
{
#ifdef DBG_SEND
	uint8_t i = 0;
	DBG_SendStr("Si4432_Init\n");
#endif
    Si4432_InitHardware();
    Si4432_ConfigFreg();
	Si4432_ModeStandBy();
#ifdef DBG_SEND
	uint8_t buf[128];
	for (i = 0; i < 128; i++)
	{
		buf[i] = Si4432_ReadReg(i);
		//DBG_SendBuffer(&buf[i], 1);
	}
	DBG_SendBuffer(buf, sizeof(buf));
#endif
}
