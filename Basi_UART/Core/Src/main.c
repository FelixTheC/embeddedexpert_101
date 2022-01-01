#include <stdio.h>
#include "stm32f4xx.h"

// APB1 (bit 17)	: 	USART2
// alternate func	:	AFRL bit 7
// USART_BRR
// USART_CR1 		:	bit 13, 3


void init_USART2(void);
void write_USART2(int ch);
void delayMS(int delay);

int __io_putchar(int ch)
{
	write_USART2(ch);
	return ch;
}

int main(void)
{
	init_USART2();
	char text[] = "Hello from the NUCLEO\r\n";

	while(1)
	{
		printf(text);
		delayMS(10);
	}

	return 0;
}


void init_USART2(void)
{
	// enable clock for USART
	RCC->APB1ENR |= (1<<17);

	// enable clock for GPIO_A to use alternate function to enable USART
	RCC->AHB1ENR |= (1<<0);

	// 0 => alternate function low; 1 => alternate function high
	GPIOA->AFR[0] = 0x0700; // (AFRL2) 0111 0000 0000
	GPIOA->MODER |= (1<<5);	// Set PA2 to alternate function (AFRL2 correspond to PA2)

	USART2->BRR = 0x0683; 	// Set Baudrate to 9600 @16MhZ
	USART2->CR1 |= (1<<3); 	// Enable TE
	USART2->CR1 |= (1<<13); // Enable UE
}

void write_USART2(int ch)
{
	// wait while TX buffer is empty
	while(!(USART2->SR & 0x0080)) {}

	USART2->DR = (ch & 0xFF);
}

void delayMS(int delay)
{
	int i;
	for(;delay > 0; --delay)
	{
		for(i = 0; i < 3195; ++i);
	}
}
