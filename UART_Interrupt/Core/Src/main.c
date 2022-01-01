#include "stm32f4xx.h"
#include "systickdelayms.h"

void init_USART2(void);
void LED_on(int value);


int main(void)
{

	__disable_irq();

	RCC->AHB1ENR |= (1<<0);
	GPIOA->MODER |= (1<<10); 	// set PA5 to output

	init_USART2();
	USART2->CR1 |= (1<<5);		// Enable RX Interrupt

	NVIC_EnableIRQ(USART2_IRQn);

	__enable_irq();

	while(1) {}
}


void init_USART2(void)
{
	RCC->APB1ENR |= (1<<17);	// enable clock for USART
	RCC->AHB1ENR |= (1<<0);		// enable clock for GPIO_A to use alternate function to enable USART

	// 0 => alternate function low; 1 => alternate function high
	GPIOA->AFR[0] = 0x07000; 	// (AFRL2) 0111 0000 0000 0000
	GPIOA->MODER |= (1<<7);		// Set PA2 to alternate function (AFRL2 correspond to PA2)

	USART2->BRR = 0x008b; 		// Set Baudrate to 115200 @ 16MhZ
	USART2->CR1 = (1<<2); 		// Enable RE
	USART2->CR1 |= (1<<13); 	// Enable UE
}

void LED_on(int value)
{
	value %= 16;
	for(;value > 0; --value)
	{
		GPIOA->BSRR = (1<<5);
		systickDelayMS(100);
		GPIOA->BSRR = (1<<21);
	}

	systickDelayMS(400);
}

void USART2_IRQHandler(void)
{
	char chr;
	if(USART2->SR & 0x0020)
	{
		chr = USART2->DR;
		LED_on(chr);
	}
}
