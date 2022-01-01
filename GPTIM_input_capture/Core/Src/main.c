#include "stm32f4xx.h"

int TIMESTAMP = 0;

int main(void)
{
	RCC->AHB1ENR |= (1<<0);
	GPIOA->MODER |= (1<<11);	// set PA5 to alternate function

	GPIOA->AFR[0] |= (1<<20);	// set AFRL5 (which correspond to PA5) to AF1

	RCC->APB1ENR |= (1<<0);
	TIM2->PSC = 1600 - 1;
	TIM2->ARR = 10000 - 1;
	TIM2->CCMR1 = 0x30;			// set output to toggle on match
	TIM2->CCR1 = 0;				// set match mode
	TIM2->CCER |= (1<<0);		// Enable ch1 to compare mode
	TIM2->CNT = 0;				// Clear Counter
	TIM2->CR1 = 1;				// Enable TIM2


	// Configure PA6 as input of TIM3 CH1
	RCC->AHB1ENR |= (1<<0);

	GPIOA->MODER |= (1<<13);	// set PA6 to alternate function
	GPIOA->AFR[0] |= (1<<25);	// set AFRL6 (which correspond to PA6) to AF2

	// Configure TIM3
	RCC->APB1ENR |= (1<<1);
	TIM3->PSC = 1600 - 1;
	TIM3->CCMR1 = 0x41;			// set ch1 capture at every edge
	TIM3->CCER = 1;
	TIM3->CR1 = 1;

	while(1)
	{
		while(!(TIM3->SR & 2)) {}
		TIMESTAMP = TIM3->CCR1;
	}

	return 0;
}
