#include "uart.h"
#include "stm32f4xx.h"
#include <stdio.h>
#include <stdint.h>

#define GPIOAEN        (1U<<0)
#define UART2EN        (1U<<17)

#define SYS_FREQ       16000000
#define APB1_CLK       SYS_FREQ
#define UART_BAUDRATE  115200

#define CR1_TE         (1U<<3)
#define CR1_UE         (1U<<13)

#define SR_TXE         (1U<<7)

static uint16_t compute_uart_baud_rate(uint32_t periph_clk, uint32_t baudrate);
static void uart_set_baud_rate(uint32_t periph_clk, uint32_t baudrate);
static void uart_write(int ch);

int __io_putchar(int ch)
{
	uart_write(ch);
	return ch;
}

void uart_tx_init(void)
{
	/* Enable clock access to GPIOA */
	RCC->AHB1ENR |= GPIOAEN;

	/* Set PA2 mode to alternate function mode */
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |=(1U<<5);

	/* Set alternate function type to AF7 (UART2_TX) */
	GPIOA->AFR[0] |=(1u<<8);
	GPIOA->AFR[0] |=(1u<<9);
	GPIOA->AFR[0] |=(1u<<10);
	GPIOA->AFR[0] &=~(1u<<11);

	/* Enable clock access to UART2 */
	RCC->APB1ENR |= UART2EN;

	/* Configure baud rate and transfer direction */
	uart_set_baud_rate(APB1_CLK, UART_BAUDRATE);

	USART2->CR1 = CR1_TE;

	/* Enable UART module */
	USART2->CR1 |= CR1_UE;
}

static void uart_write(int ch)
{
	/* Make sure the transmit data register is empty */
	while(!(USART2->SR & SR_TXE)){}
	/* Write to transmit data register */
	USART2->DR = (ch & 0xFF);
}

static void uart_set_baud_rate(uint32_t periph_clk, uint32_t baudrate)
{
	USART2->BRR = compute_uart_baud_rate(periph_clk, baudrate);
}


static uint16_t compute_uart_baud_rate(uint32_t periph_clk, uint32_t baudrate)
{
	 return ((periph_clk + (baudrate/2U))/baudrate);
}

