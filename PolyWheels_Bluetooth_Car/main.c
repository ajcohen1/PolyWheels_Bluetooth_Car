#include "msp.h"
#include "MotorDriver.h"
#include "UART.h"

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	MotorDriver_init();
	UART_init();

	__enable_irq();

	while(1);
}
