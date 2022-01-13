/*
 * GLCD_ST7735.h
 *
 *  Created on: Jan 13, 2022
 *      Author: felix
 */

#ifndef INC_GLCD_ST7735_H_
#define INC_GLCD_ST7735_H_

#include "stm32f4xx_hal.h"

#define LCD_RST1 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET)
#define LCD_RST0 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET)

#define LCD_DC1 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET)
#define LCD_DC0 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET)

#define LCD_CS1 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET)
#define LCD_CS0 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET)

SPI_HandleTypeDef hspi2;

void init_GPIO_ST7735(void);
void init_SPI_ST7735(void);
void init_8bit_SPI(void);
void init_16bit_SPI(void);
void ST7725_send_data_8bit(unsigned char data);
void ST7725_send_data_16bit(uint8_t msb, uint8_t lsb);
void ST7725_send_data(unsigned char data);
void ST7725_send_command(unsigned char data);
void ST7725_Init_Cmd(void);
void ST7725_Init(void);


#endif /* INC_GLCD_ST7735_H_ */
