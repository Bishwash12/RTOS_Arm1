#include "led.h"
#include "uart.h"
#include "timebase.h"

int main(void)
{
	led_init();
	uart_tx_init();
	timebase_init();

	while(1)
	{
		delay(1);
		printf("Hello from STM32F4......\n");
	}
}
