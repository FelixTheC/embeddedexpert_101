#include "stm32f4xx.h"

/*
 * Configure systick to interrupt to toggle LED
 * at 1Hz, system clock is 16 MHz
 */

const unsigned int ONE_HERTZ = 16000000;
const unsigned int ONE_KILO_HERTZ = 16000;

int main(void)
{
	__disable_irq();

	RCC->AHB1ENR |= (1<<0);
	GPIOA->MODER |= (1<<10);	// set PA5 as output

	SysTick->LOAD = (ONE_HERTZ * 1) - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = 7;

	__enable_irq();

	while(1) {}
}


void SysTick_Handler(void)
{
	GPIOA->ODR ^= (1<<5);
}
