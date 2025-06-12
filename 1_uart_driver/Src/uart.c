#include "uart.h"
#include "stm32f4xx.h"

#define GPIOAEN        (1U<<0)

void uart_tx_init(void)
{
	/* Enable clock access to GPIOA */
	RCC->AHB1ENR |= GPIOAEN;

	/* Set PA2 mode to alternate function mode */
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |=(1U<<5);

	/* Set alternate function type to AF7 (UART2_TX) */

	/* Enable clock access to UART2 */
	/* Configure baud rate and transfer direction */
}

