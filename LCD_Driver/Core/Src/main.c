#include "stm32f4xx.h"
#include "systickdelayms.h"

// PC0 - PC7 = D0 - D7
// PB5 = RS
// PB6 = R/W
// PB7 = EN


#define RS (1<<5)	// Enable bit 5
#define RW (1<<6)	// Enable bit 6
#define EN (1<<7)	// Enable bit 7


void init_GPIO(void);
void LCD_command(unsigned char command);
void LCD_data(char data);
void LCD_commit(void);
void init_LCD(void);
void delayMs(int delay);

enum LCD_COMMAND{CLEAR_SCREEN=0x01,
				 CURSOR_HOME=0x02,
				 CURSOR_RIGHT=0x06,
				 DISPLAY_ON=0x0F,
				 BEGIN_LINE_1=0x80,
				 BEGIN_LINE_2=0xC0,
				 DATA_8_BIT=0x38,
				 DATA_4_BIT=0x28,
				 INIT=0x30
				};


int main(void)
{
	init_LCD();

	const char *text = "Hello World";
	const short size_t = 12;

	while (1)
	{
		for(int i=0; i < size_t; ++i)
		{
			LCD_data(text[i]);
			LCD_commit();
		}

		systickDelayMS(500);

	}
}


void init_LCD(void)
{
	init_GPIO();

	// init sequence
	systickDelayMS(30);
	LCD_command(INIT);
	LCD_commit();
	systickDelayMS(10);
	LCD_command(INIT);
	LCD_commit();
	systickDelayMS(1);
	LCD_command(INIT);
	LCD_commit();

	LCD_command(DATA_8_BIT);		// 2-line, 5x7 font
	LCD_commit();
	LCD_command(CURSOR_RIGHT);
	LCD_commit();
	LCD_command(CLEAR_SCREEN);
	LCD_commit();
	LCD_command(DISPLAY_ON);		// on and blinky cursor

}


void init_GPIO(void)
{
	// I could made it also with one assignment but this is more readable
	RCC->AHB1ENR |= (1<<1);		// Enable clock for PB
	RCC->AHB1ENR |= (1<<2);		// Enable clock for PC

	GPIOB->MODER |= (1<<10);	// Enable RS
	GPIOB->MODER |= (1<<12);	// Enable RW
	GPIOB->MODER |= (1<<14);	// Enable EN

	GPIOB->BSRR |= 0x00C;		// 0000 1100 set EN and RW low

	// set PC0 - PC7 as output
	GPIOC->MODER |= 0x005555;	// 0000 0000 0101 0101 0101 0101
}


void LCD_command(unsigned char command)
{
	GPIOB->BSRR = ((RS | RW)<<16);	// RS=0, R/W = 0
	GPIOC->ODR = command;
}


void LCD_data(char data)
{
	GPIOB->BSRR = RS;				// RS=1
	GPIOB->BSRR = (RW<<16);			// R/W=0
	GPIOC->ODR = data;
}


void LCD_commit(void)
{
	GPIOB->BSRR = EN;
	systickDelayMS(1);
	GPIOB->BSRR = (EN<<16); 		// clear EN
}

