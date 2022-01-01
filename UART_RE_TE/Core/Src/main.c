#include "stm32f4xx.h"
#include <stdio.h>


void init_USART2(void);
int read_USART2(void);
int write_USART2(int ch);

struct __FILE
{
	int handle;
};

FILE __stdin	= {0};
FILE __stdout	= {1};
FILE __stderr	= {2};


int main(void)
{
	init_USART2();

	while(1)
	{
		puts("Hello from the NUCLEO\r\n");
	}

	return 0;
}


void init_USART2(void)
{
	// enable clock for GPIO_A to use alternate function to enable USART
	RCC->AHB1ENR |= (1<<0);

	// enable clock for USART
	RCC->APB1ENR |= (1<<17);

	// 0 => alternate function low; 1 => alternate function high
	GPIOA->AFR[0] |= 0x7700; 	// (AFRL3 + AFRL2) 0111 0111 0000 0000
	GPIOA->MODER |= (1<<7);		// Set PA3 to alternate function (AFRL3 correspond to PA3)
	GPIOA->MODER |= (1<<5);		// Set PA2 to alternate function (AFRL2 correspond to PA2)

	USART2->BRR = 0x0683; 		// Set Baudrate to 9600 @16MhZ
	USART2->CR1 = (1<<2); 		// Enable RE
	USART2->CR1 |= (1<<3); 		// Enable TE
	USART2->CR1 |= (1<<13); 	// Enable UE
}


int read_USART2(void)
{

	// 0x0020 => get bit 5
	while(!(USART2->SR & 0x0020)) {}
	return USART2->DR;
}


int write_USART2(int ch)
{
	// 0x0020 => get bit 7
	while(!(USART2->SR & 0x0080)) {}
	USART2->DR = (ch & 0xFF);
	return ch;
}


int fgetc(FILE *f)
{
	int chr;
	chr = read_USART2();

	if (chr == '\r')
	{
		write_USART2(chr);
		chr = '\n';
	}
	write_USART2(chr);

	return chr;
}


int fputc(int chr, FILE *f)
{
	return write_USART2(chr);
}
