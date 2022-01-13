#include "GLCD_ST7735.h"


int main(void)
{
	HAL_Init();
	ST7725_Init();

	while (1) {
		ST7725_send_data('H');
		ST7725_send_data('i');
	}

	return 0;
}
