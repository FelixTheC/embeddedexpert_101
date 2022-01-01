#include "stm32f4xx.h"
/*
 *
 * Toggle LED at 1Hz using TIM2 Compare mode.
 *
 */


int main(void)
{
	RCC->AHB1ENR |= (1<<0);
	GPIOA->MODER |= (1<<11);	// set PA5 to alternate function

	GPIOA->AFR[0] |= (1<<20);	// set AFRL5 (which correspond to PA5) to AF1

	RCC->APB1ENR |= (1<<0);
	TIM2->PSC = 1600 - 1;
	TIM2->ARR = 10000;
	TIM2->CCMR1 = 0x30;			// set output to toggle on match
	TIM2->CCR1 = 0;				// set match mode
	TIM2->CCER |= (1<<0);		// Enable ch1 to compare mode
	TIM2->CNT = 0;				// Clear Counter
	TIM2->CR1 = 1;				// Enable TIM2

	while(1)
	{

	}

	return 0;
}
