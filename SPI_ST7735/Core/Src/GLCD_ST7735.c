#include "GLCD_ST7735.h"


void init_GPIO_ST7735(void)
{
	// SPI2 PINS

	// RES:		PB5
	// DC:		PB4
	// CS:		PB3

	__GPIOB_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;		// Enable Push Pull
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;

	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


void init_SPI_ST7735(void)
{
	hspi2.Instance = 			SPI2;
	hspi2.Init.Mode = 			SPI_MODE_MASTER;
	hspi2.Init.Direction = 		SPI_DIRECTION_1LINE;
	hspi2.Init.DataSize = 		SPI_DATASIZE_8BIT;
	hspi2.Init.CLKPolarity = 	SPI_POLARITY_LOW;
	hspi2.Init.CLKPhase = 		SPI_PHASE_1EDGE;
	hspi2.Init.NSS = 			SPI_NSS_SOFT;

	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;

	// can be omitted
	hspi2.Init.FirstBit = 			SPI_TIMODE_DISABLED;
	hspi2.Init.CRCCalculation = 	SPI_CRCCALCULATION_DISABLED;
	hspi2.Init.CRCPolynomial = 		10;

	HAL_SPI_Init(&hspi2);
}

void init_8bit_SPI(void)
{
	hspi2.Init.DataSize = 		SPI_DATASIZE_8BIT;
	HAL_SPI_Init(&hspi2);
}

void init_16bit_SPI(void)
{
	hspi2.Init.DataSize = 		SPI_DATASIZE_16BIT;
	HAL_SPI_Init(&hspi2);
}

void ST7725_send_data_8bit(unsigned char data)
{
	// SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout in ms
	HAL_SPI_Transmit(&hspi2, &data, 1, 0x01);
}

void ST7725_send_data_16bit(uint8_t msb, uint8_t lsb)
{
	uint8_t listData[] = {lsb, msb};
	HAL_SPI_Transmit(&hspi2, listData, 1, 0x01);
}

void ST7725_send_data(unsigned char data)
{
	LCD_DC1;
	ST7725_send_data_8bit(data);
}

void ST7725_send_command(unsigned char data)
{
	LCD_DC0;
	ST7725_send_data_8bit(data);
}

void ST7725_Init_Cmd(void)
{
	/**
	 * Init the sub-device
	 */

	LCD_CS0;
	LCD_RST0;

	HAL_Delay(10);

	LCD_RST1;

	HAL_Delay(10);

	ST7725_send_command(0x11);

	HAL_Delay(120);

	ST7725_send_command(0x3A);		// Set color mode
	ST7725_send_data(0x05);

	ST7725_send_command(0x36);
	ST7725_send_data(0x14);

	ST7725_send_command(0x29);		// Display on
}

void ST7725_Init(void)
{
	init_GPIO_ST7735();
	init_SPI_ST7735();
	ST7725_Init_Cmd();
}
