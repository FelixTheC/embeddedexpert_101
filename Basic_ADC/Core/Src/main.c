#include "stm32f4xx.h"

/*
 * Configure ADC CH1
 */

int analogValue;

int main(void)
{
	RCC->AHB1ENR |= (1<<0);
	GPIOA->MODER |= 0xC;		// Set PA1 to analog

	RCC->APB2ENR |= (1<<8);		// Enable clock access to ADC
	ADC1->CR2 = 0;				// Disable ADC
	ADC1->SQR3 = 1;
	ADC1->CR2 |= (1<<0);		// Enable ADC

	while (1)
	{
		ADC1->CR2 |= (1<<30);
		// wait for conversion to be complete
		while(!(ADC1->SR & 2)){}

		analogValue = ADC1->DR;
	}

}
