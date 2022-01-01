#include "stm32f4xx.h"


int main(void)
{

	RCC->AHB1ENR |= (1<<0);  	// set bit 0 to 1
	GPIOA->MODER |= (1<<10);	// set bit 10 to 1 to enable General purpose output mode

	//TIM2 Config
	RCC->APB1ENR |= (1<<0);		// set bit 0 to 1
	TIM2->PSC = 1600 - 1;		// Divide the System clock source(16MhZ) by 1600
	TIM2->ARR = 10000 - 1;		// Divide the rest 10000 from the PSC by 10000 which gives us 1MhZ;
	TIM2->CNT = 0;				// Clear timer counter
	TIM2->CR1 = 1;				// Enable TIM2

	while(1)
	{
		while(!(TIM2->SR & 1)) {}
		TIM2->SR &= ~1;

		GPIOA->ODR ^= (1<<5);	// switch bit 5
	}

	return 0;
}
