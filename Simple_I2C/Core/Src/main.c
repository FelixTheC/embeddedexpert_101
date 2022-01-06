#include "stm32f4xx.h"


// SCL - PB8
// SDA - PB9
void delayMs(int n);
void init_I2C();
int readbyte_I2C(char saddr, char maddr, char *data);


int main(void)
{
	init_I2C();
}


void init_I2C()
{
	RCC->AHB1ENR |= (1<<2);
	RCC->APB1ENR |= (1<<21);

	// enable alternative function
	GPIOB->MODER |= (1<<17);
	GPIOB->MODER |= (1<<19);

	// set alternate function as I2C
	GPIOB->AFR[1] |= (1<<2);
	GPIOB->AFR[1] |= (1<<6);
	GPIOB->OTYPER |= (3<<8);		// set as open-drain

	// set as pull-up
	GPIOB->PUPDR |= (1<<16);
	GPIOB->PUPDR |= (1<<18);

	I2C1->CR1 = 0x8000;				// software reset
	I2C1->CR2 = (1<<2);				// 2MHz
	I2C1->CCR = 80;					// standard mode, 100kHz clock
	I2C1->TRISE = 17;				// mx rise time
	I2C1->CR1 |= (1<<0);

}



int readbyte_I2C(char saddr, char maddr, char *data)
{
	volatile int tmp;
	while(I2C1->SR2 & 2) {} 		// make sure bus is not busy

	I2C1->CR1 |= 0x100;				// start
	while(I2C1->SR1 & 1) {}


	I2C1->DR |= saddr << 1;
	while(!(I2C1->SR1 & 2)) {}
	tmp = I2C1->SR2;

	while(!(I2C1->SR1 & 0x80)) {}
	I2C1->DR = maddr;
	while(!(I2C1->SR1 & 0x80)) {}

	I2C1->CR1 |= 0x100;
	while(!(I2C1->SR1 & 1)) {}
	I2C1->CR1 = saddr << 1 | 1;

	while(!(I2C1->SR1 & 2)) {}
	I2C1->CR1 &= ~0x400;
	tmp = I2C1->SR2;

	I2C1->CR1 |= 0x200;

	while(!(I2C1->SR1 & 0x40)) {}
	*++data = I2C1->DR;

	return 0;
}

void delayMs(int n)
{
	for(;n > 0; --n)
		for(int i = 0; i < 3195; ++i);
}


