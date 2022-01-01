#include "stm32f4xx.h"


/*
 * Create TIM2 to toggle LED at 1Hz
 * System clock is 16MHz
 */

int main(void)
{
	__disable_irq();

	RCC->AHB1ENR |= (1<<0);
	GPIOA->MODER |= (1<<10);	// set PA5 to output

	//TIM2
	RCC->APB1ENR |= (1<<0);
	TIM2->PSC = 16000 - 1;
	TIM2->ARR = 1000 - 1;
	TIM2->CR1 = (1<<0);			// enable Counter CEN
	TIM2->DIER = (1<<0);		// enable UIE (Update Interrupt Enable)

	NVIC_EnableIRQ(TIM2_IRQn);

	__enable_irq();

	while(1) {}
}

void TIM2_IRQHandler(void)
{
	TIM2->SR = 0;
	GPIOA->ODR ^= (1<<5);
}
