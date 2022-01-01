#include "stm32f4xx.h"
#include "systickdelayms.h"


/*
 * LED: 	PA5
 * Button: 	PC13
 *
*/
void setup_interrupt(void);

volatile int ledToggleOn = 0;


int main(void)
{

	__disable_irq();				// disable global interrupts
	setup_interrupt();
	__enable_irq();

	while (1)
	{

	}

}

void setup_interrupt(void)
{
	RCC->AHB1ENR |= (1<<0);			// Enable Port A
	RCC->AHB1ENR |= (1<<2);			// Enable Port C
	RCC->APB2ENR |= (1<<14);		// Enable SYSCFG Clock

	GPIOA->MODER |= (1<<10);		// set PA5 to output
	GPIOC->MODER |= 0x00000000;		// set PC13 to input

	SYSCFG->EXTICR[3] |= (1<<5);	// select port C for EXTI13 in configuration register 4

	EXTI->IMR |= (1<<13);			// unmask EXTI13
	EXTI->FTSR |= (1<<13);			// select falling edge trigger
	EXTI->RTSR |= (1<<13);

	NVIC_EnableIRQ(EXTI15_10_IRQn);
}


void EXTI15_10_IRQHandler(void)
{
	if(ledToggleOn == 0)
	{
		GPIOA->BSRR = (1<<5);			// enable PA5
		ledToggleOn = 1;
	}
	else if(ledToggleOn == 1)
	{
		GPIOA->BSRR = (1<<21);			// reset PA5
		ledToggleOn = 0;
	}

	EXTI->PR |= (1<<13);			// clear interrupt
}
