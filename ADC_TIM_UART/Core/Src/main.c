#include "stm32f4xx.h"


void init_ADC(void);
void init_USART2(void);
void init_TIM2(void);
void write_USART2(int ch);


int __io_putchar(int ch)
{
	write_USART2(ch);
	return ch;
}



int main(void)
{

	int data;
	double celsius;
	const double VOLTAGE = 3.3;
	const short BITSIZE = 4095;		// 12 bit

	RCC->AHB1ENR |= (1<<0);
	RCC->APB1ENR |= (1<<0);

	init_TIM2();
	init_USART2();
	init_ADC();

	while(1)
	{
		while(!(ADC1->SR)) {}

		data = ADC1->DR;
		double tmp = (double)data / BITSIZE * VOLTAGE;	// data divide by 12bit times the voltage
		celsius = ((tmp - 0.76)/0.0025) + 25;
		printf("Temperature: %.2f°C\r\n", celsius);
	}
}

void init_USART2(void)
{
	// enable clock for USART
	RCC->APB1ENR |= (1<<17);

	// enable clock for GPIO_A to use alternate function to enable USART
	RCC->AHB1ENR |= (1<<0);

	// 0 => alternate function low; 1 => alternate function high
	GPIOA->AFR[0] = 0x0700; // (AFRL2) 0111 0000 0000
	GPIOA->MODER |= (1<<5);	// Set PA2 to alternate function (AFRL2 correspond to PA2)

	USART2->BRR = 0x0683; 	// Set Baudrate to 9600 @16MhZ
	USART2->CR1 |= (1<<3); 	// Enable TE
	USART2->CR1 |= (1<<13); // Enable UE
}


void init_ADC(void)
{
	RCC->APB2ENR |= (1<<8);		// Enable clock access to ADC

	ADC->CCR |= (1<<23);		// Enable Temperature Sensor
	ADC->CCR &= ~(1<<22);		// Disable VBATE

	ADC1->SMPR1 |= (1<<20);		// set SMP16 (Channel 16) to minimum 84 cycles
	ADC1->SQR3 = 16;			// Temperature Sensor is internal connected to Channel 16
	ADC1->CR2 |= 0x13000000;		// Enable ADC EXTEN raising edge
	ADC1->CR2 |= (1<<0);
}

void init_TIM2(void)
{
	TIM2->PSC = 1600 - 1;
	TIM2->ARR = 10000 - 1;
	TIM2->CNT = 0;
	TIM2->CCMR1 = 0x6800;
	TIM2->CCER = (1<<4);
	TIM2->CCR2 = 50 - 1;
	TIM2->CR1 = (1<<0);
}

void write_USART2(int ch)
{
	// wait while TX buffer is empty
	while(!(USART2->SR & 0x0080)) {}

	USART2->DR = (ch & 0xFF);
}
