#include "stm32f4xx.h"


// APB1 (bit 17)	: 	USART2
// alternate func	:	AFRL bit 7
// USART_BRR
// USART_CR1 		:	bit 13, 2, 3

#define PIN5		(1<<5);
#define LED_PIN		PIN5

void init_USART2(void);
char read_USART2(void);
void write_USART2(int ch);
void LED_on(int value);
void delayMS(int delay);
void writeInfo();


int main(void)
{
	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= (1<<10);

	init_USART2();

	char ch;
	while(1)
	{
		ch = read_USART2();
		LED_on(ch);
		writeInfo();
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

	USART2->BRR = 0x008B; 		// Set Baudrate to 115200 @16MhZ
	USART2->CR1 |= (1<<2); 		// Enable RE
	USART2->CR1 |= (1<<3); 		// Enable TE
	USART2->CR1 |= (1<<13); 	// Enable UE
}

char read_USART2(void)
{
	while(!(USART2->SR & 0x0020)) {}  // wait until char arrives

	return USART2->DR;
}

void write_USART2(int ch)
{
	// wait while TX buffer is empty
	while(!(USART2->SR & 0x0080)) {}

	USART2->DR = (ch & 0xFF);
}

void LED_on(int value)
{
	value %= 16;
	for(;value > 0; --value)
	{
		GPIOA->ODR ^= LED_PIN;
		delayMS(100);
		GPIOA->ODR ^= LED_PIN;
	}

	delayMS(400);
}

void delayMS(int delay)
{
	int i;
	for(;delay > 0; --delay)
	{
		for(i = 0; i < 3195; ++i);
	}
}

void writeInfo()
{
	const char text[] = "Welcome to NUCLEO\r\n";
	const unsigned short size_t = 20;
	unsigned short chr;

	for(chr = 0; chr < size_t; ++chr)
	{
		write_USART2(text[chr]);
	}
}



