/*
 * Where is the LED connected
 *
 * Port: 	A
 * Pin:		5
 *
 */

#include "stm32f4xx.h"


#define GPIOAEN		0x01;
#define PIN5		0x020;
#define LED_PIN		PIN5


void systickDelayMS(int ms);

int main(void)
{
	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= 0x400;
	GPIOA->MODER &= ~0x800;

	while(1)
	{
		GPIOA->ODR ^= LED_PIN;
		systickDelayMS(300);
	}

	return 0;
}

void systickDelayMS(int ms)
{
	unsigned int i;
	SysTick->LOAD = 16000; 	// Reload with number of clocks per millisecond
	SysTick->VAL = 0;		// Clear current value register
	SysTick->CTRL = 0x5;	// Enable SysTick

	for(i = 0; i < ms; ++i)
	{
		// Wait until the COUNT flag is set
		while((SysTick->CTRL & 0x10000) == 0) {}
	}

	SysTick->CTRL = 0;
}


