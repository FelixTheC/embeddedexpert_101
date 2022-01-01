#include "stm32f4xx.h"


int main(void)
{
	RCC->AHB1ENR |= (1<<0);

	GPIOA->MODER |= (1<<11);	// set PA5
	GPIOA->AFR[0] |= (1<<20);	// set PA5 for TIM2

	// Timer setup
	RCC->APB1ENR |= (1<<0);
	TIM2->PSC = 10 - 1; 		// divide by 10
	TIM2->ARR = 26667 - 1;
	TIM2->CNT = 0;
	TIM2->CCMR1 = 0x60;			// set PWM mode 1
	TIM2->CCER = (1<<0);		// enable PWM ch1
	TIM2->CCR1 = 8889 - 1;		// pulse width 1/3 the period
	TIM2->CR1 = (1<<0);			// enable timer


	while(1)
	{

	}

	return 0;
}
