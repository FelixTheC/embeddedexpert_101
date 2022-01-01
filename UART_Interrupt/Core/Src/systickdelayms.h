/*
 * systickdelayms.h
 *
 *  Created on: Jan 1, 2022
 *      Author: felix
 */

#ifndef SRC_SYSTICKDELAYMS_H_
#define SRC_SYSTICKDELAYMS_H_

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

#endif /* SRC_SYSTICKDELAYMS_H_ */
